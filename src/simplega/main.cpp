#include <boost/program_options.hpp>
#include <iostream>
#include "data/GraphSerializer.hpp"
#include "data/PathSerializer.hpp"
#include "data/ConfigSerializer.hpp"
#include "genetic/GeneticSolver.hpp"
#include "genetic/GeneticAnalyser.hpp"
#include "net/PopulationExchanger.hpp"
#include "utils/Random.hpp"

#define LOG_ALWS std::cout << "[ALWS] "
#define LOG_INFO if(!logQuiet) std::cout << "[INFO] "
#define LOG_ERR std::cerr << "[ERROR] "

namespace po = boost::program_options;

tsp::Graph graph;
tsp::GeneticSolver solver(graph);
tsp::Config cfg;
tsp::PopulationExchanger *ex = NULL;
bool logQuiet = false;

static int parseArguments(int argc, char **argv)
{
    po::variables_map vm;
    po::options_description desc("Allowed Options");
    desc.add_options()
    ("help,h", "show help text")
    ("quiet,q", "activate quiet mode")
    ("config,c", po::value<std::string>(), "config file")
    ("infile,i", po::value<std::string>(), "graph definition file")
    ("outfile,o", po::value<std::string>(), "path output file")
    ("generations,g", po::value<unsigned int>(),
     "amount of generations to be calculated")
    ("population,p", po::value<unsigned int>(), "population size")
    ("start,s", po::value<unsigned int>(), "start node")
    ("elitism,e", po::value<double>(), "elitism rate")
    ("mutation,m", po::value<double>(), "mutation chance")
    ("fitness,f", po::value<unsigned int>(), "fitness power")
    ("exchange,x", po::value<double>(), "exchange rate")
    ("network,n", "activate MPI network mode")
    ;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch(std::exception &e) {
        std::cout << e.what() << "\n";
        return 1;
    }

    // check if required options were given
    bool hasConfig = vm.count("config");
    bool hasOpt = vm.count("infile") &&
                  vm.count("outfile") &&
                  vm.count("generations") &&
                  vm.count("population") &&
                  vm.count("start") &&
                  vm.count("elitism") &&
                  vm.count("mutation") &&
                  vm.count("fitness");
    bool hasHelp = vm.count("help");
    if(hasHelp || !(hasConfig || hasOpt)) {
        std::cout << desc << "\n";
        return 1;
    }

    logQuiet = vm.count("quiet") > 0;

    // create network component if we are in network mode
    if(vm.count("network")) {
        LOG_INFO << "Network mode activated.\n";
        ex = new tsp::PopulationExchanger(argc, argv);

        // seed the random number generator with our rank and time
        int seed = (ex->getRank() + 1) * std::time(0);
        LOG_ALWS << "Seed " << seed << "\n";
        tsp::Random::shakeRNG(seed);

        // if we are not master then return here and
        // receive config through network
        if(!ex->isMaster())
            return 0;
    }

    // load config file if specified
    if(hasConfig) {
        LOG_INFO << "Loading Config from '" << vm["config"].as<std::string>() <<
                  "' ...\n";
        if(!tsp::ConfigSerializer::load(cfg, vm["config"].as<std::string>())) {
            LOG_ERR << " Failed\n";
            return 1;
        }
    }

    // set all config parameters
    if(vm.count("exchange"))
        cfg.exchangeRate = vm["exchange"].as<double>();
    if(vm.count("infile"))
        cfg.graphFile = vm["infile"].as<std::string>();
    if(vm.count("outfile"))
        cfg.pathFile = vm["outfile"].as<std::string>();
    if(vm.count("generations"))
        cfg.generationCount = vm["generations"].as<unsigned int>();
    if(vm.count("population"))
        cfg.gaSettings.populationSize = vm["population"].as<unsigned int>();
    if(vm.count("start"))
        cfg.gaSettings.startNode = vm["start"].as<unsigned int>();
    if(vm.count("elitism"))
        cfg.gaSettings.elitismRate = vm["elitism"].as<double>();
    if(vm.count("mutation"))
        cfg.gaSettings.mutationChance = vm["mutation"].as<double>();
    if(vm.count("fitness"))
        cfg.gaSettings.fitnessPow = vm["fitness"].as<unsigned int>();

    return 0;
}

static void exchangeConfig()
{
    if(ex == NULL)
        return;

    ex->exchangeConfig(cfg);
    ex->setExchangeCount(cfg.exchangeRate * cfg.gaSettings.populationSize);

    return;
}

static void printParameters()
{
    LOG_INFO << "Parameters\n";
    LOG_INFO << "  graph file: " << cfg.graphFile << "\n";
    LOG_INFO << "  path file: " << cfg.pathFile << "\n";
    LOG_INFO << "  generation count: " << cfg.generationCount << "\n";
    LOG_INFO << "  population size: " << cfg.gaSettings.populationSize << "\n";
    LOG_INFO << "  start node: " << cfg.gaSettings.startNode << "\n";
    LOG_INFO << "  elitism rate: " << cfg.gaSettings.elitismRate << "\n";
    LOG_INFO << "  mutation chance: " << cfg.gaSettings.mutationChance << "\n";
    LOG_INFO << "  fitness power: " << cfg.gaSettings.fitnessPow << "\n";
    LOG_INFO << "  exchange rate: " << cfg.exchangeRate << "\n";
}

static void printCurrentGen(tsp::GeneticAnalyser &analyser)
{
    LOG_INFO << "  Best Distance: " << analyser.getBestDistance(
                  solver.getPopulation()) << "\n";
    LOG_INFO << "  Mean Distance: " << analyser.getMeanDistance(
                  solver.getPopulation()) << "\n";
    LOG_INFO << "  Best Fitness: " << analyser.getBestFitness(
                  solver.getPopulation()) << "\n";
    LOG_INFO << "  Mean Fitness: " << analyser.getMeanFitness(
                  solver.getPopulation()) << "\n";
    LOG_INFO << "  Best Norm. Fitness: " << analyser.getBestNormalizedFitness(
                  solver.getPopulation()) << "\n";
}

static int loadGraph()
{
    LOG_INFO << "Loading Graph ...\n";
    if(!tsp::GraphSerializer::load(graph, cfg.graphFile)) {
        LOG_ERR << " Failed\n";
        return 1;
    }

    return 0;
}

static void runAlgorithm()
{
    if(ex == NULL || ex->isMaster()) {
        LOG_ALWS << "Solving TSP ...\n";
    }

    LOG_INFO << "Initializing solver...";
    solver.setSettings(cfg.gaSettings);
    solver.init();

    tsp::GeneticAnalyser analyser(graph);
    for(unsigned int i = 0; i < cfg.generationCount; ++i) {

        LOG_INFO << "Calculating Generation " << i + 1 << "...\n";
        solver.nextGeneration();

        if(ex != NULL) {
            LOG_INFO << "Exchanging individuals ...\n";
            ex->exchange(solver.getPopulation());
        }

        LOG_INFO << "Updating fitness ...\n";
        solver.updateFitness();

        printCurrentGen(analyser);
    }

    if(ex != NULL) {
        LOG_INFO << "Gathering best individuals ...\n";
        ex->gather(solver.getPopulation());

        if(ex->isMaster())
        {
            solver.updateFitness();
            LOG_ALWS << "Received " << solver.getPopulation().getIndividuals().size() << " solutions\n";
            for(unsigned int i = 0; i < solver.getPopulation().getIndividuals().size(); ++i)
                LOG_ALWS << "  solution " << i << ": " << analyser.getDistance(solver.getPopulation().getIndividuals()[i]) << "\n";
        }
    }

    if(ex == NULL || ex->isMaster()) {

        LOG_ALWS << "=============================\n";
        LOG_ALWS << "Final Results\n";
        LOG_ALWS << "  Best Distance: " <<  analyser.getBestDistance(
                      solver.getPopulation()) << "\n";
    }
}

static int savePath()
{

    if(ex != NULL && !ex->isMaster())
        return 0;

    LOG_ALWS << "Saving Path ...\n";
    if(!tsp::PathSerializer::save(
                solver.getPopulation().getBestIndividual().getPath(),
                cfg.pathFile)) {
        std::cout << " Failed\n";
        return 1;
    }


    return 0;
}

int main(int argc, char **argv)
{
    tsp::Random::shakeRNG();

    int ret = parseArguments(argc, argv);
    if(ret)
        return ret;

    exchangeConfig();
    printParameters();

    ret = loadGraph();
    if(ret)
        return ret;

    runAlgorithm();

    ret = savePath();
    if(ret)
        return ret;

    if(ex != NULL)
        delete ex;

    return 0;
}

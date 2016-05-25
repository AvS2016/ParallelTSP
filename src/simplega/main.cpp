#include <boost/program_options.hpp>
#include <iostream>
#include "data/GraphSerializer.hpp"
#include "data/PathSerializer.hpp"
#include "data/ConfigSerializer.hpp"
#include "genetic/GeneticSolver.hpp"
#include "genetic/GeneticAnalyser.hpp"
#include "utils/Random.hpp"

namespace po = boost::program_options;

tsp::Graph graph;
tsp::GeneticSolver solver(graph);
tsp::Config cfg;

int parseArguments(int argc, char **argv)
{
    po::variables_map vm;
    po::options_description desc("Allowed Options");
    desc.add_options()
    ("help,h", "show help text")
    ("config,c", po::value<std::string>(), "config file")
    ("infile,i", po::value<std::string>(), "graph definition file")
    ("outfile,o", po::value<std::string>(), "path output file")
    ("generations,g", po::value<unsigned int>(), "amount of generations to be calculated")
    ("population,p", po::value<unsigned int>(), "population size")
    ("start,s", po::value<unsigned int>(), "start node")
    ("elitism,e", po::value<double>(), "elitism rate")
    ("mutation,m", po::value<double>(), "mutation chance")
    ("fitness,f", po::value<unsigned int>(), "fitness power")
    ;
    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch(std::exception &e) {
        std::cout << e.what() << "\n";
        return 1;
    }

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
    if( hasHelp || !(hasConfig || hasOpt))
    {
        std::cout << desc << "\n";
        return 1;
    }

    if(hasConfig)
    {
        std::cout << "Loading Config from '" << vm["config"].as<std::string>() << "' ...";
        std::cout.flush();
        if(!tsp::ConfigSerializer::load(cfg, vm["config"].as<std::string>()))
        {
            std::cout << " Failed\n";
            return 1;
        }
        std::cout << " Done\n";
    }

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


int main(int argc, char **argv)
{
    tsp::Random::shakeRNG();

    int ret = parseArguments(argc, argv);
    if(ret)
        return ret;

    std::cout << "Parameters\n";
    std::cout << "  graph file: " << cfg.graphFile << "\n";
    std::cout << "  path file: " << cfg.pathFile << "\n";
    std::cout << "  generation count: " << cfg.generationCount << "\n";
    std::cout << "  population size: " << cfg.gaSettings.populationSize << "\n";
    std::cout << "  start node: " << cfg.gaSettings.startNode << "\n";
    std::cout << "  elitism rate: " << cfg.gaSettings.elitismRate << "\n";
    std::cout << "  mutation chance: " << cfg.gaSettings.mutationChance << "\n";
    std::cout << "  fitness power: " << cfg.gaSettings.fitnessPow << "\n";

    std::cout << "Loading Graph ...";
    std::cout.flush();
    if(!tsp::GraphSerializer::load(graph, cfg.graphFile))
    {
        std::cout << " Failed\n";
        return 1;
    }
    std::cout << " Done\n";

    std::cout << "Initializing solver...";
    std::cout.flush();
    solver.setSettings(cfg.gaSettings);
    solver.init();
    std::cout << " Done\n";

    tsp::GeneticAnalyser analyser(graph);
    for(unsigned int i = 0; i < cfg.generationCount; ++i) {
        std::cout << "Calculating Generation " << i + 1 << "... ";
        std::cout.flush();
        solver.nextGeneration();
        std::cout << " Done\n";
        std::cout << "  Best Distance: " << analyser.getBestDistance(solver.getPopulation()) << "\n";
        std::cout << "  Mean Distance: " << analyser.getMeanDistance(solver.getPopulation()) << "\n";
        std::cout << "  Best Fitness: " << analyser.getBestFitness(solver.getPopulation()) << "\n";
        std::cout << "  Mean Fitness: " << analyser.getMeanFitness(solver.getPopulation()) << "\n";
        std::cout << "  Best Norm. Fitness: " << analyser.getBestNormalizedFitness(solver.getPopulation()) << "\n";
    }

    std::cout << "Saving Path ...";
    std::cout.flush();
    tsp::PathSerializer::save(solver.getPopulation().getBestIndividual().getPath(),
                              cfg.pathFile);
    std::cout << " Done\n";

    return 0;
}

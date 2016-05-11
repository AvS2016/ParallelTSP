#include <boost/program_options.hpp>
#include <iostream>
#include "data/GraphSerializer.hpp"
#include "data/PathSerializer.hpp"
#include "genetic/GeneticSolver.hpp"
#include "genetic/PopulationAnalyzer.hpp"

namespace po = boost::program_options;

tsp::Graph graph;
tsp::GeneticSolver solver(graph);
po::variables_map vm;

int parseArguments(int argc, char **argv)
{
    po::options_description desc("Allowed Options");
    desc.add_options()
        ("help,h", "show help text")
        ("start,s", po::value<unsigned int>(), "start node in graph")
        ("population,p", po::value<unsigned int>(), "population size")
        ("generations,g", po::value<unsigned int>(), "amount of generations to be calculated")
        ("infile,i", po::value<std::string>(), "graph definition file")
        ("outfile,o", po::value<std::string>(), "path output file")
    ;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch (std::exception &e) {
        std::cout << e.what() << "\n";
        return 1;
    }

    if (vm.count("help") ||
            !vm.count("start") ||
            !vm.count("population") ||
            !vm.count("generations") ||
            !vm.count("infile") ||
            !vm.count("outfile")) {
        std::cout << desc << "\n";
        return 1;
    }

    return 0;
}


int main(int argc, char **argv)
{
    int ret = parseArguments(argc, argv);
    if(ret)
        return ret;

    std::cout << "Loading Graph from '" << vm["infile"].as<std::string>() << "'...";
    std::cout.flush();
    tsp::GraphSerializer::load(graph, vm["infile"].as<std::string>());
    std::cout << "Done\n";

    tsp::GeneticSolver::Settings s;
    s.startNode = vm["start"].as<unsigned int>();
    s.populationSize = vm["population"].as<unsigned int>();
    s.mutationChance = 0.01;

    solver.setSettings(s);
    solver.init();

    for(unsigned int i = 0; i < vm["generations"].as<unsigned int>(); ++i)
    {
        std::cout << "Calculating Generation " << i + 1 << "... ";
        std::cout.flush();
        solver.nextGeneration();
        std::cout << "Done\n";
        std::cout << "  Best Distance: " << solver.getBest().getDistance() << "\n";
        std::cout << "  Best Normalized: " << solver.getBest().getNormalizedFitness() << "\n";
        std::cout << "  Mean Distance: " << tsp::PopulationAnalyzer::getMeanFitness(solver.getPopulation()) << "\n";
    }

    std::cout << "Saving Path to '" << vm["outfile"].as<std::string>() << "'... ";
    std::cout.flush();
    tsp::PathSerializer::save(solver.getBest().getPath(), vm["outfile"].as<std::string>());
    std::cout << "Done\n";

    return 0;
}

#include <boost/program_options.hpp>
#include <iostream>
#include "GraphGenerator.hpp"
#include "data/GraphSerializer.hpp"

namespace po = boost::program_options;

tsp::Graph graph;
po::variables_map vm;

int parseArguments(int argc, char **argv)
{
    po::options_description desc("Allowed Options");
    desc.add_options()
    ("help,h", "show help text")
    ("width,W", po::value<int>(), "define width of the map")
    ("height,H", po::value<int>(), "define height of the map")
    ("nodes,n", po::value<int>(), "define number of nodes")
    ("file,f", po::value<std::string>(), "path to file")
    ;

    try {
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
    } catch(std::exception &e) {
        std::cout << e.what() << "\n";
        return 1;
    }

    if(vm.count("help") ||
            !vm.count("width") ||
            !vm.count("height") ||
            !vm.count("nodes") ||
            !vm.count("file")) {
        std::cout << desc << "\n";
        return 1;
    }

    return 0;
}

int generateGraph()
{
    tsp::GraphGenerator gen;

    std::cout << "Graph Generator" << "\n";
    std::cout << "===============" << "\n";
    std::cout << "Parameters:" << "\n";
    std::cout << "-- width:  " << vm["width"].as<int>() << "\n";
    std::cout << "-- height: " << vm["height"].as<int>() << "\n";
    std::cout << "-- nodes:  " << vm["nodes"].as<int>() << "\n";
    std::cout << "Generating graph ..." << "\n";
    gen.setSettings(vm["width"].as<int>(),
                    vm["height"].as<int>(),
                    vm["nodes"].as<int>());
    gen.generate(graph);

    std::cout << "Saving graph ..." << "\n";
    if(!tsp::GraphSerializer::save(graph, vm["file"].as<std::string>()))
        return -1;
    std::cout << "Saved to '" <<  vm["file"].as<std::string>() << "'\n";

    return 0;
}

int main(int argc, char **argv)
{
    int ret = parseArguments(argc, argv);
    if(ret)
        return ret;

    ret = generateGraph();
    if(ret)
        return ret;

    return 0;
}

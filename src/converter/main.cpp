#include <boost/program_options.hpp>
#include <iostream>
#include "GraphConverter.hpp"
#include "data/GraphSerializer.hpp"

// gnuplot: http://downloads.sourceforge.net/project/gnuplot/gnuplot/5.0.3/gnuplot-5.0.3.tar.gz?r=https%3A%2F%2Fsourceforge.net%2Fprojects%2Fgnuplot%2Ffiles%2Fgnuplot%2F5.0.3%2F&ts=1462465110&use_mirror=pilotfiber

namespace po = boost::program_options;

tsp::Graph graph;
po::variables_map vm;

int parseArguments(int argc, char **argv)
{
    po::options_description desc("Allowed Options");
    desc.add_options()
        ("help,h", "show help text")
        ("graph,g", po::value<std::string>(), "path to graph file")
        ("path,p", po::value<std::string>(), "path to path file")
        ("plot,o", po::value<std::string>(), "output path")
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
            !vm.count("graph") ||
            !vm.count("path")) {
        std::cout << desc << "\n";
        return 1;
    }

    return 0;
}

int convertGraph()
{
    tsp::GraphConverter conv;

    std::cout << "Graph Converter" << std::endl;
    std::cout << "===============" << std::endl;
    std::cout << "Parameters:" << std::endl;
    std::cout << "-- graph: " << vm["graph"].as<std::string>() << std::endl;
    std::cout << "-- path:  " << vm["path"].as<std::string>() << std::endl;
    std::cout << "-- plot:  " << vm["plot"].as<std::string>() << std::endl;

    std::cout << "Loading graph ..." << std::endl;
    if (!tsp::GraphSerializer::load(graph, vm["graph"].as<std::string>()))
    {
        std::cout << "File not found!" << std::endl;
        return 1;
    }
    else
    {
        std::cout << "Creating plot script ..." << std::endl;
        int res = conv.createPlot(graph, vm["path"].as<std::string>(), "tsp.dat");
        switch (res){
            case 0:
                std::cout << "Script created." << std::endl;
                break;
            case 1:
                std::cout << "Can´t parse path." << std::endl;
                return 1;
            case 2:
                std::cout << "Parsed path is not valid." << std::endl;
                return 1;
        }

        // std::cout << "Drawing graph ..." << std::endl;
        // if (conv.drawGraph("tsp.svg"))
        // {
        //     std::cout << "Graph saved to file." << std::endl;
        // }
        // else
        // {
        //     std::cout << "Error while drawing the graph." << std::endl;
        //     return 1;
        // }
    }

    return 0;
}

int main(int argc, char **argv)
{
    int ret = parseArguments(argc, argv);
    if(ret)
        return ret;

   ret = convertGraph();
   if(ret)
       return ret;

    return 0;
}

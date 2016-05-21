#include <iostream>
#include <fstream>
#include <cmath>
#include "../data/PathSerializer.hpp"
#include "GraphConverter.hpp"

namespace tsp
{

    GraphConverter::GraphConverter()
    : pathFile_(""), dataFile_(""), plotFile_(""), resultFile_("")
    {
    }

    GraphConverter::~GraphConverter()
    {
    }

    int GraphConverter::createPlot(Graph &graph, const std::string &pathFile, const std::string &resultFile)
    {
        pathFile_ = pathFile;
        dataFile_ = "tsp.dat";
        plotFile_ = "tsp.plt";
        resultFile_ = resultFile;

        // serialize path
        Path path;

        PathSerializer::load(path, pathFile_);
        
        // write *.dat file
        std::ofstream os(dataFile_);
        os << "#TSP Points\n";
        for(unsigned int i = 0; i < path.size(); ++i){
            uint nodeId = path[i];
            if (nodeId < graph.size()) 
                os << graph[nodeId].x() << " " << graph[nodeId].y() << std::endl;
        }
        os.close();
        
        // write *.plt file
        os.open(plotFile_, std::ofstream::out);
        os << "set terminal svg size 350,262 fname 'Verdana' fsize 10" << std::endl;
        os << "set output '" << resultFile_ << "'" << std::endl;
        os << "set title 'TSP Graph Visualisation (points: " << path.size() << ")'" << std::endl;
        os << "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.0   # --- blue" << std::endl;
        os << "plot '" << dataFile_ << "' with linespoints ls 1" << std::endl;
        os.close();

        return 0;
    }

    bool GraphConverter::drawGraph()
    {
    	const std::string cmd = "gnuplot " + plotFile_;
    	system(cmd.c_str());
    	//TODO: delete temporary files
        return true;
    }

}

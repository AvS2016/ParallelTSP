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

    int GraphConverter::createPlot(Graph &graph, const std::string& pathFile, const std::string& dataFile)
    {
        pathFile_ = pathFile;
        dataFile_ = dataFile;

        tsp::Path path;
        tsp::PathSerializer pathSerializer;

        pathSerializer.load(path, pathFile_);
        
        std::ofstream os(dataFile_);
        os << "#TSP Points\n";

        for(unsigned int i = 0; i < path.size(); ++i){
            uint nodeId = path[i];
            if (nodeId < graph.size()) 
                os << graph[nodeId].x() << " " << graph[nodeId].y() << "\n";
        }

        os << "\n";
        os.close();
        
        return 0;
    }

    bool GraphConverter::drawGraph(const std::string& plotFile)
    {

        resultFile_ = plotFile;
        return true;
    }

}

#include <iostream>
#include <fstream>
#include <cmath>
#include <json/json.h>
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

        //json convert path to array
        Json::Value root;
        Json::Reader reader;

        std::ifstream is(pathFile_);
        if(!reader.parse(is, root, false))
            return 1;
        if(!root.isArray())
            return 2;
        
        std::ofstream os(dataFile_);
        os << "#TSP Points\n";

        for(unsigned int i = 0; i < root.size(); ++i){
            uint nodeId = root[i].asUInt();
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

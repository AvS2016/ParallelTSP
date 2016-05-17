#ifndef GENERATOR_GRAPHCONVERTER_HPP_
#define GENERATOR_GRAPHCONVERTER_HPP_

#include "data/Graph.hpp"

namespace tsp
{

    class GraphConverter
    {
    private:
        std::string pathFile_;
        std::string dataFile_;
        std::string plotFile_;
        std::string resultFile_;

    public:
        GraphConverter();
        ~GraphConverter();

        int createPlot(Graph &graph, const std::string& pathFile, const std::string& dataFile);
        bool drawGraph(const std::string& plotFile);
    };

}

#endif

#ifndef GENERATOR_GRAPHCONVERTER_HPP_
#define GENERATOR_GRAPHCONVERTER_HPP_

#include "data/Graph.hpp"

namespace tsp
{

    class GraphConverter
    {
    private:
        std::string filename_;

    public:
        GraphConverter();
        ~GraphConverter();

        bool drawGraph(Graph &graph, std::string filename);
    };

}

#endif

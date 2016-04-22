#ifndef GENERATOR_GRAPHGENERATOR_HPP_
#define GENERATOR_GRAPHGENERATOR_HPP_

#include "data/Graph.hpp"

namespace tsp
{

    class GraphGenerator
    {
    private:
        int width_;
        int height_;
        int nodes_;
        int edges_;

        void addEdge(Graph &graph, int start, int end);
    public:
        GraphGenerator();
        ~GraphGenerator();

        void setSettings(int width, int height, int nodes, int edges);

        void generate(Graph &graph);
    };

}

#endif

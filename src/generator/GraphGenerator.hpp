#ifndef GENERATOR_GRAPHGENERATOR_HPP_
#define GENERATOR_GRAPHGENERATOR_HPP_

#include "data/Graph.hpp"
#include <map>

namespace tsp
{

    class GraphGenerator
    {
    private:
        int width_;
        int height_;
        int nodes_;
        std::map<std::string, bool> exists_;
        std::string generateNodeID(int x, int y);
    public:
        GraphGenerator();
        ~GraphGenerator();

        void setSettings(int width, int height, int nodes);

        void generate(Graph &graph);
    };

}

#endif

#ifndef GENERATOR_GRAPHGENERATOR_HPP_
#define GENERATOR_GRAPHGENERATOR_HPP_

#include "data/Graph.hpp"
#include <map>

namespace tsp
{

    class GraphGenerator
    {
    private:
        unsigned int width_;
        unsigned int height_;
        unsigned int nodes_;
        std::map<std::string, bool> exists_;
        std::string generateNodeID(int x, int y);
    public:
        GraphGenerator();
        ~GraphGenerator();

        void setSettings(const unsigned int width, const unsigned int height,
                         const unsigned int nodes);

        void generate(Graph &graph);
    };

}

#endif

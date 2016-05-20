#include <cmath>
#include <sstream>
#include "GraphGenerator.hpp"
#include "utils/Random.hpp"

namespace tsp
{

    GraphGenerator::GraphGenerator()
        : width_(0), height_(0), nodes_(0)
    {
    }

    GraphGenerator::~GraphGenerator()
    {
    }

    void GraphGenerator::setSettings(const unsigned int width, const unsigned int height, const unsigned int nodes)
    {
        width_ = width;
        height_ = height;
        nodes_ = nodes;
    }

    std::string GraphGenerator::generateNodeID(int x, int y)
    {
        std::stringstream ss;
        ss << x << "/" << y;
        return ss.str();
    }

    void GraphGenerator::generate(Graph &graph)
    {
        exists_.clear();
        std::string id;
        graph.resize(nodes_);
        for(unsigned int i = 0; i < nodes_; ++i) {
            int x, y;
            do {

                x = Random::nextInt(width_);
                y = Random::nextInt(height_);
                id = generateNodeID(x, y);
            } while(exists_.find(id) != exists_.end());

            exists_[id] = true;
            graph[i] = Node(i, x, y);
        }
    }

}

#include <cmath>
#include <sstream>
#include "GraphGenerator.hpp"

namespace tsp
{

    GraphGenerator::GraphGenerator()
        : width_(0), height_(0), nodes_(0), rand_()
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

        graph.setWidth(width_);
        graph.setHeight(height_);
        graph.resize(nodes_);
        for(unsigned int i = 0; i < nodes_; ++i) {
            int x, y;
            do {

                x = rand_.nextInt(width_);
                y = rand_.nextInt(height_);
                id = generateNodeID(x, y);
            } while(exists_.find(id) != exists_.end());

            exists_[id] = true;
            graph[i] = Node(i, x, y);
        }
    }

}

#include "GraphGenerator.hpp"
#include <iostream>

namespace tsp
{

    GraphGenerator::GraphGenerator()
    : width_(0), height_(0), nodes_(0), edges_(0)
    {
    }

    GraphGenerator::~GraphGenerator()
    {
    }

    void GraphGenerator::setSettings(int width, int height, int nodes,
            int edges)
    {
        width_ = width;
        height_ = height;
        nodes_ = nodes;
        edges_ = edges;
    }

    void GraphGenerator::generate(Graph& graph)
    {
        graph.nodes().resize(nodes_);
        for(int i = 0; i < nodes_; ++i)
        {
            int x = rand() % width_;
            int y = rand() % width_;
            graph.nodes()[i] = Node(i, x, y);
        }

        for(int i = 0; i < nodes_; ++i)
        {
            int start = rand() % nodes_;
            int end = rand() % nodes_;
            Edge e(start, end);
            graph.edges()[e.id()] = e;
        }
    }

}

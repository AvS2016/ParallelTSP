#include <iostream>
#include <cmath>
#include "GraphGenerator.hpp"

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

    void GraphGenerator::addEdge(Graph &graph, int start, int end)
    {
        Node a = graph.nodes()[start];
        Node b = graph.nodes()[end];
        float dx = (float) a.x() - (float) b.x();
        float dy = (float) a.y() - (float) b.y();
        float weight = sqrtf(dx * dx + dy * dy);

        Edge e(start, end, weight);
        graph.edges()[e.id()] = e;
    }

    void GraphGenerator::generate(Graph& graph)
    {
        int edgeCount = 0;
        graph.nodes().resize(nodes_);
        for(int i = 0; i < nodes_; ++i)
        {
            int x = rand() % width_;
            int y = rand() % width_;
            graph.nodes()[i] = Node(i, x, y);
            if(i > 1)
            {
                int end = i;
                while (end == i)
                    end = rand() % i;
                addEdge(graph, i, end);
                addEdge(graph, end, i);
                edgeCount += 2;
            }
        }

        for(; edgeCount < edges_; ++edgeCount)
        {
            int start = rand() % nodes_;
            int end = rand() % nodes_;
            addEdge(graph, start, end);
        }
    }

}

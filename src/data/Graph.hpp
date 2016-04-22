#ifndef DATA_GRAPH_HPP_
#define DATA_GRAPH_HPP_

#include <vector>
#include <map>
#include "data/Node.hpp"
#include "data/Edge.hpp"

namespace tsp
{

    class Graph
    {
    private:
        std::vector<Node> nodes_;
        std::map<std::string, Edge> edges_;
    public:
        Graph()
        { }

        ~Graph()
        { }

        std::vector<Node>& nodes()
        {
            return nodes_;
        }
        std::map<std::string, Edge>& edges()
        {
            return edges_;
        }
    };

}

#endif

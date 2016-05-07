#ifndef DATA_PATHVERIFIER_HPP_
#define DATA_PATHVERIFIER_HPP_

#include "data/Graph.hpp"

namespace tsp
{

    class PathVerifier
    {
    private:
        PathVerifier()
        { }
        ~PathVerifier()
        { }

    public:
        bool verify(const Graph &graph, const Path &path);
    };

}

#endif

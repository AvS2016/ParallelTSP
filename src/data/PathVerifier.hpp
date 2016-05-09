#ifndef DATA_PATHVERIFIER_HPP_
#define DATA_PATHVERIFIER_HPP_

#include "data/Graph.hpp"
#include "data/Path.hpp"

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
        static bool verify(const Graph &graph, const Path &path);
    };

}

#endif

#include "PathVerifier.hpp"

namespace tsp
{
    bool PathVerifier::verify(const Graph &graph, const Path &path)
    {
        std::vector<int> visited(graph.size());
        for(unsigned int i = 0; i < visited.size(); ++i)
            visited[i] = 0;

        if(path.front() != path.back())
            return false;

        // count visits per node
        for(int node : path) {
            if(node >= static_cast<int>(visited.size()))
                return false;
            visited[node] += 1;
        }

        // check how many times node was visited
        bool startNode = false;
        for(int count : visited) {
            if(count == 2) {
                if(startNode)
                    return false;
                else {
                    startNode = true;
                    continue;
                }
            }

            if(count != 1)
                return false;
        }

        return true;
    }
}

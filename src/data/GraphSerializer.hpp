#ifndef DATA_GRAPHSERIALIZER_HPP_
#define DATA_GRAPHSERIALIZER_HPP_

#include <istream>
#include "data/Graph.hpp"

namespace tsp
{
    class GraphSerializer
    {
    private:
        GraphSerializer()
        { }
        ~GraphSerializer()
        { }

    public:
        static bool deserialize(Graph &graph, std::istream &is);
        static bool serialize(Graph &graph, std::ostream &os);
        static bool load(Graph &graph, const std::string &file);
        static bool save(Graph &graph, const std::string &file);
    };
}

#endif


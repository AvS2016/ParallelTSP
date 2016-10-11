#ifndef GENERATOR_GRAPHCONVERTER_HPP_
#define GENERATOR_GRAPHCONVERTER_HPP_

#include "data/Graph.hpp"
#include "data/Path.hpp"

namespace tsp
{

    class GraphConverter
    {
    private:
        bool drawPath_;
        std::string dataFile_;
        std::string plotFile_;
        std::string resultFile_;

    public:
        GraphConverter(const bool drawPath);
        ~GraphConverter();

        bool savePlot(const Graph &graph, const Path& path,
                       const std::string &fileName);
    };

}

#endif

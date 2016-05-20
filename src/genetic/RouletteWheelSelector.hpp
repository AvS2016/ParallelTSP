#ifndef GENETIC_ROULETTEWHEELSELECTOR_HPP_
#define GENETIC_ROULETTEWHEELSELECTOR_HPP_

#include "data/Graph.hpp"
#include "genetic/Population.hpp"

namespace tsp
{
    class RouletteWheelSelector
    {
    private:
        const Graph &graph_;
    public:
        RouletteWheelSelector(const Graph &graph);
        ~RouletteWheelSelector();

        void select(const Population &population, std::vector<int> &parents);
    };

}

#endif

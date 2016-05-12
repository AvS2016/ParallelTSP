#ifndef GENETIC_FITNESSUPDATER_HPP_
#define GENETIC_FITNESSUPDATER_HPP_

#include "data/Graph.hpp"
#include "genetic/Population.hpp"

namespace tsp
{

    class FitnessUpdater
    {
    private:
        const Graph &graph_;
    public:
        FitnessUpdater(const Graph &graph);
        ~FitnessUpdater();

        void update(Population &population);
    };

}

#endif

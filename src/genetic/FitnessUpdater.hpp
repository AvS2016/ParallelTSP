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
        unsigned int fitnessPow_;
    public:
        FitnessUpdater(const Graph &graph);
        ~FitnessUpdater();

        void setFitnessPow(const unsigned int pow);
        void update(Population &population);
    };

}

#endif

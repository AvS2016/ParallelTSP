#ifndef GENETIC_POPULATION_HPP_
#define GENETIC_POPULATION_HPP_

#include "genetic/Individual.hpp"

namespace tsp
{
    class Population
    {
    private:
        std::vector<Individual> individuals_;
    public:
        Population() {
        }
        ~Population() {
        }

        std::vector<Individual> &getIndividuals() {
            return individuals_;
        }

        const std::vector<Individual> &getIndividuals() const {
            return individuals_;
        }

        const Individual &getBestIndividual() const {
            return individuals_.back();
        }
    };
}

#endif

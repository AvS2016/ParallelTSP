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
        Population()
        { }
        ~Population()
        { }

        std::vector<Individual>& getIndividuals()
        {
            return individuals_;
        }

        double getMeanFitness()
        {
            double sum = 0;
            for (Individual &ind: individuals_)
                sum += ind.getFitness();

            return sum / individuals_.size();
        }

        double getMeanDistance()
        {
            double sum = 0;
            for (Individual &ind: individuals_)
                sum += ind.getDistance();

            return sum / individuals_.size();
        }
    };
}

#endif

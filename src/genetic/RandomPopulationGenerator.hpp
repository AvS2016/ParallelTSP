#ifndef GENETIC_RANDOMPOPULATIONGENERATOR_HPP_
#define GENETIC_RANDOMPOPULATIONGENERATOR_HPP_

#include "genetic/Population.hpp"

namespace tsp
{
    class RandomPopulationGenerator
    {
    private:
        const Graph& graph_;
        unsigned int startNode_;
    public:
        RandomPopulationGenerator(const Graph &graph, const unsigned int startNode);
        ~RandomPopulationGenerator();

        void generateIndividual(Individual &individual);
        void generatePopulation(Population &population, const unsigned int size);

    };

}

#endif

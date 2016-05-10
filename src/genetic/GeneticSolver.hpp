#ifndef GENETIC_GENETICSOLVER_HPP_
#define GENETIC_GENETICSOLVER_HPP_

#include "data/Graph.hpp"
#include "genetic/OrderedCrossover.hpp"
#include "genetic/RandomPopulationGenerator.hpp"
#include "genetic/SwapMutation.hpp"

namespace tsp
{
    class GeneticSolver
    {
    public:
        struct Settings {
            unsigned int startNode;
            unsigned int populationSize;
            double mutationChance;
        };

        enum ReproductionState
        {
            DEAD = 0,
            SELECTED,
            CROSSED,
            BREEDED,
            MUTATED
        };

    private:
        const Graph &graph_;
        Settings settings_;

        Population *currPopulation_;
        Population *nextPopulation_;

        std::vector<int> parents_;

        OrderedCrossover crossover_;
        RandomPopulationGenerator populationGen_;
        SwapMutation mutator_;

        void updateFitness();
        void select();
        void crossover();
        void mutate();

    public:
        GeneticSolver(const Graph& graph);
        ~GeneticSolver();

        void setSettings(const Settings &settings);
        void init();
        void nextGeneration();

        Individual &getBest();
        Population &getPopulation();
    };

}

#endif

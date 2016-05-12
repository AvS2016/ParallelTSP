#ifndef GENETIC_GENETICSOLVER_HPP_
#define GENETIC_GENETICSOLVER_HPP_

#include "utils/Random.hpp"
#include "genetic/FitnessUpdater.hpp"
#include "genetic/RouletteWheelSelector.hpp"
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

    private:
        const Graph &graph_;
        Settings settings_;
        Random rand_;

        Population *currPopulation_;
        Population *nextPopulation_;

        std::vector<int> parents_;

        FitnessUpdater fitnessUpdater_;
        RouletteWheelSelector selector_;
        OrderedCrossover crossover_;
        RandomPopulationGenerator populationGen_;
        SwapMutation mutator_;

        void updateFitness();
        void select();
        void crossover();
        void mutate();
        void swapPopulations();

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

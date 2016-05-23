#ifndef GENETIC_GENETICSOLVER_HPP_
#define GENETIC_GENETICSOLVER_HPP_

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
            double elitismRate;
            unsigned int fitnessPow;
        };

    private:
        const Graph &graph_;
        Settings settings_;

        Population *currPopulation_;
        Population *nextPopulation_;

        std::vector<int> parents_;

        FitnessUpdater fitnessUpdater_;
        RouletteWheelSelector selector_;
        OrderedCrossover crossover_;
        RandomPopulationGenerator populationGen_;
        SwapMutation mutator_;

        unsigned int eliteCount_;

        unsigned int getElitismCount();
        void updateFitness();
        void select();
        void applyElite();
        void crossover();
        void mutate();
        void swapPopulations();

    public:
        GeneticSolver(const Graph &graph);
        ~GeneticSolver();

        void setSettings(const Settings &settings);
        void init();
        void nextGeneration();

        Population &getPopulation();
    };

}

#endif

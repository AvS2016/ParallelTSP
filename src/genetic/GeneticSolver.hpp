#ifndef GENETIC_GENETICSOLVER_HPP_
#define GENETIC_GENETICSOLVER_HPP_

#include "data/Graph.hpp"

namespace tsp
{
    class GeneticSolver
    {
    public:
        struct Settings {
            unsigned int populationSize;
        };

    private:
        const Graph &graph_;
        Settings settings_;

        void generateInitialPopulation();

    public:
        GeneticSolver(const Graph& graph);
        ~GeneticSolver();

        void setSettings(const Settings &settings);
        void nextGeneration();
    };

}

#endif

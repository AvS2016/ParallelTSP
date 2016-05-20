#ifndef GENETIC_GENETICANALYSER_HPP_
#define GENETIC_GENETICANALYSER_HPP_

#include "data/Graph.hpp"
#include "genetic/Population.hpp"

namespace tsp
{

    class GeneticAnalyser
    {
    private:
        const Graph &graph_;
        std::vector<double> distances_;
    public:
        GeneticAnalyser(const Graph &graph);
        ~GeneticAnalyser();

        double getDistance(const Individual &ind);

        double getBestDistance(const Population &pop);
        double getBestFitness(const Population &pop);
        double getBestNormalizedFitness(const Population &pop);

        double getMeanDistance(const Population &pop);
        double getMeanFitness(const Population &pop);
        double getMeanNormalizedFitness(const Population &pop);
    };

}

#endif

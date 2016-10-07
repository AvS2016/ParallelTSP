#include "GeneticAnalyser.hpp"

#include <cmath>

#define STRETCH_FACTOR (10)

namespace tsp
{

    static double calcNodeDistance(const Node &n1, const Node &n2)
    {
        double dx = n1.x() - n2.x();
        double dy = n1.y() - n2.y();
        return sqrt(dx * dx + dy * dy);
    }

    GeneticAnalyser::GeneticAnalyser(const Graph &graph)
        : graph_(graph)
    {

    }

    GeneticAnalyser::~GeneticAnalyser()
    {

    }

    double GeneticAnalyser::getDistance(const Individual &ind)
    {
        double sum = 0;
        for(unsigned int i = 0; i + 1 < ind.getPath().size(); ++i) {
            const Node &n1 = graph_[ind.getPath()[i]];
            const Node &n2 = graph_[ind.getPath()[i + 1]];
            sum += calcNodeDistance(n1, n2);
        }
        return sum;
    }

    double GeneticAnalyser::getBestDistance(const Population &pop)
    {
        return getDistance(pop.getBestIndividual());
    }

    double GeneticAnalyser::getBestFitness(const Population &pop)
    {
        return pop.getBestIndividual().getFitness();
    }

    double GeneticAnalyser::getBestNormalizedFitness(const Population &pop)
    {
        return pop.getBestIndividual().getNormalizedFitness();
    }

    double GeneticAnalyser::getMeanDistance(const Population &pop)
    {
        distances_.resize(pop.getIndividuals().size());

        double max = 0;
        for(unsigned int i = 0; i < distances_.size(); ++i) {
            distances_[i] = GeneticAnalyser::getDistance(pop.getIndividuals()[i]);
            if(distances_[i] > max)
                max = distances_[i];
        }

        double sum = 0;
        for(unsigned int i = 0; i < distances_.size(); ++i)
            sum += STRETCH_FACTOR * (distances_[i] / max);

        sum = sum / distances_.size();
        return sum * (max / STRETCH_FACTOR);
    }

    double GeneticAnalyser::getMeanFitness(const Population &pop)
    {
        double sum = 0;
        for(const Individual &ind : pop.getIndividuals())
            sum += ind.getFitness();
        return sum / pop.getIndividuals().size();
    }

    double GeneticAnalyser::getMeanNormalizedFitness(const Population &pop)
    {
        double sum = 0;
        for(const Individual &ind : pop.getIndividuals())
            sum += ind.getNormalizedFitness();
        return sum / pop.getIndividuals().size();
    }

}

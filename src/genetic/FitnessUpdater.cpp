#include <cassert>
#include <cmath>
#include <algorithm>

#include "FitnessUpdater.hpp"
#include "data/PathVerifier.hpp"

namespace tsp
{

    static double nodeDistance(const Node &n1, const Node &n2)
    {
        double dx = n1.x() - n2.x();
        double dy = n1.y() - n2.y();
        return std::sqrt(dx * dx + dy * dy);
    }

    static bool lessNormalizedFitness(const Individual &i1,
                                      const Individual &i2)
    {
        return i1.getNormalizedFitness() < i2.getNormalizedFitness();
    }

    FitnessUpdater::FitnessUpdater(const Graph &graph)
        : graph_(graph)
    {
    }

    FitnessUpdater::~FitnessUpdater()
    {
    }

    void FitnessUpdater::update(Population &population)
    {
        // calculate distance and find maximum
        double maxDistance = 0;
        for(Individual & ind : population.getIndividuals()) {
            assert(PathVerifier::verify(graph_, ind.getPath()));

            double accumDistance = 0;
            for(unsigned int i = 0; i + 1 < ind.getPath().size(); ++i) {
                Node curr = graph_[ind.getPath()[i]];
                Node next = graph_[ind.getPath()[i + 1]];
                accumDistance += nodeDistance(curr, next);
            }
            ind.setDistance(accumDistance);
            if(accumDistance > maxDistance)
                maxDistance = accumDistance;
        }

        // calc fitness relative to maximum distance (shorter = greater fitness)
        double fitnessSum = 0;
        for(Individual & ind : population.getIndividuals()) {
            double fitness = maxDistance / ind.getDistance();
            fitness = fitness * fitness;
            ind.setFitness(fitness);
            fitnessSum += ind.getFitness();
        }

        // calc normalized fitness
        for(Individual & ind : population.getIndividuals())
            ind.setNormalizedFitness(ind.getFitness() / fitnessSum);

        // sort descending to fitness
        std::sort(population.getIndividuals().begin(),
                  population.getIndividuals().end(), lessNormalizedFitness);
    }

}

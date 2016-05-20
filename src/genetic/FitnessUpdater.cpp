#include <cassert>
#include <cmath>
#include <algorithm>

#include "FitnessUpdater.hpp"
#include "data/PathVerifier.hpp"

#define FITNESS_POW 50

namespace tsp
{

    static double nodeDistanceSq(const Node &n1, const Node &n2)
    {
        double dx = n1.x() - n2.x();
        double dy = n1.y() - n2.y();
        return dx * dx + dy * dy;
    }

    static bool lessNormalizedFitness(const Individual &i1,
                                      const Individual &i2)
    {
        return i1.getNormalizedFitness() < i2.getNormalizedFitness();
    }

    FitnessUpdater::FitnessUpdater(const Graph &graph)
        : graph_(graph), distances_()
    {
    }

    FitnessUpdater::~FitnessUpdater()
    {
    }

    void FitnessUpdater::init()
    {
        distances_.resize(graph_.size());
    }

    double FitnessUpdater::calcScaledDistance(const Path &path)
    {
        // calculate squared distance between all nodes
        // and find maximum
        double max = 0;
        for(unsigned int i = 0; i + 1 < path.size(); ++i) {
            Node curr = graph_[path[i]];
            Node next = graph_[path[i + 1]];
            distances_[i] = nodeDistanceSq(curr, next);
            if(distances_[i] > max)
                max = distances_[i];
        }

        // calculate distance relative to maximum to prevent overflow
        double sum = 0;
        for(unsigned int i = 0; i < distances_.size(); ++i)
        {
            double val = distances_[i] / max;
            sum += val;
        }

        return sum;
    }

    void FitnessUpdater::update(Population &population)
    {
        assert(graph_.size() == distances_.size());

        // calculate scaled distance and find maximum
        double maxDistance = 0;
        for(Individual & ind : population.getIndividuals()) {
            assert(PathVerifier::verify(graph_, ind.getPath()));

            double pathDistance = calcScaledDistance(ind.getPath());
            ind.setFitness(pathDistance);
            if(pathDistance > maxDistance)
                maxDistance = pathDistance;
        }

        // calc fitness relative to maximum distance (shorter = greater fitness)
        // and find maximum to scale it down
        double maxFitness = 0;
        for(Individual & ind : population.getIndividuals()) {
            double fitness = maxDistance / ind.getFitness();
            fitness = std::pow(fitness, FITNESS_POW);
            ind.setFitness(fitness);

            if (fitness > maxFitness)
                maxFitness = fitness;
        }

        // scale fitness down and calculate sum
        double fitnessSum = 0;
        for(Individual & ind : population.getIndividuals()) {
            ind.setFitness(ind.getFitness() / maxFitness);
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

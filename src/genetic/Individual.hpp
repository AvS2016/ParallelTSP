#ifndef GENETIC_INDIVIDUAL_HPP_
#define GENETIC_INDIVIDUAL_HPP_

#include "data/Graph.hpp"

namespace tsp
{
    class Individual
    {
    private:
        Path path_;
        double fitness_;
        double normalizedFitness_;
    public:
        Individual()
        :path_(), fitness_(0), normalizedFitness_(0)
        { }

        Individual(const Path &path)
        :path_(path), fitness_(0), normalizedFitness_(0)
        { }

        ~Individual()
        { }

        void setFitness(const double fitness)
        {
            fitness_ = fitness;
        }

        double getFitness() const
        {
            return fitness_;
        }

        void setNormalizedFitness(const double fitness)
        {
            normalizedFitness_ = fitness;
        }

        double getNormalizedFitess() const
        {
            return normalizedFitness_;
        }

        Path& getPath()
        {
            return path_;
        }
    };
}

#endif

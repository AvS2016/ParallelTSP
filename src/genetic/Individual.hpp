#ifndef GENETIC_INDIVIDUAL_HPP_
#define GENETIC_INDIVIDUAL_HPP_

#include "data/Path.hpp"

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
            : path_(), fitness_(0), normalizedFitness_(0)
        {
        }

        Individual(const Path &path)
            : path_(path), fitness_(0), normalizedFitness_(0)
        {
        }

        ~Individual()
        {
        }

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

        double getNormalizedFitness() const
        {
            return normalizedFitness_;
        }

        void setPath(const Path &path)
        {
            path_ = path;
        }

        Path &getPath()
        {
            return path_;
        }

        const Path &getPath() const
        {
            return path_;
        }



    };
}

#endif

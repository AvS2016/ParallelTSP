#ifndef GENETIC_INDIVIDUAL_HPP_
#define GENETIC_INDIVIDUAL_HPP_

#include "data/Path.hpp"

namespace tsp
{
    class Individual
    {
    private:
        Path path_;
        double distance_;
        double fitness_;
        double normalizedFitness_;
    public:
        Individual()
            : path_(), distance_(0), fitness_(0), normalizedFitness_(0) {
        }

        Individual(const Path &path)
            : path_(path), distance_(0), fitness_(0), normalizedFitness_(0) {
        }

        ~Individual() {
        }

        void setDistance(const double dist) {
            distance_ = dist;
        }

        double getDistance() const {
            return distance_;
        }

        void setFitness(const double fitness) {
            fitness_ = fitness;
        }

        double getFitness() const {
            return fitness_;
        }

        void setNormalizedFitness(const double fitness) {
            normalizedFitness_ = fitness;
        }

        double getNormalizedFitness() const {
            return normalizedFitness_;
        }


        Path &getPath() {
            return path_;
        }
    };
}

#endif

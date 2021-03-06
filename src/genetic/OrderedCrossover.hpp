#ifndef GENETIC_ORDEREDCROSSOVER_HPP_
#define GENETIC_ORDEREDCROSSOVER_HPP_

#include "genetic/Individual.hpp"

namespace tsp
{
    class OrderedCrossover
    {
    private:
        std::vector<bool> childGeneInUse_;
        std::vector<bool> graphNodeInUse_;

        void initGeneTracker(const unsigned int size, const int start);
    public:
        OrderedCrossover();
        ~OrderedCrossover();

        void cross(Individual &parent1, Individual &parent2, Individual &child);
    };
}



#endif

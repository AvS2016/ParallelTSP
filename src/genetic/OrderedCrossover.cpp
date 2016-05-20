#include <cassert>
#include <iostream>
#include "OrderedCrossover.hpp"

namespace tsp
{
    OrderedCrossover::OrderedCrossover()
    {

    }

    OrderedCrossover::~OrderedCrossover()
    {

    }

    void OrderedCrossover::initGeneTracker(const unsigned int size, const int start)
    {
        childGeneInUse_.resize(size);
        graphNodeInUse_.resize(size);
        for(unsigned int i = 0; i < childGeneInUse_.size(); ++i) {
            childGeneInUse_[i] = false;
            graphNodeInUse_[i] = false;
        }

        childGeneInUse_[0] = true;
        childGeneInUse_[childGeneInUse_.size() - 1] = true;
        graphNodeInUse_[start] = true;
    }

    void OrderedCrossover::cross(Individual &parent1, Individual &parent2,
                                 Individual &child)
    {
        assert(parent1.getPath().size() == parent2.getPath().size());

        child.getPath().resize(parent1.getPath().size());
        initGeneTracker(parent1.getPath().size(), parent1.getPath()[0]);

        // set child start / end node
        child.getPath()[0] = parent1.getPath()[0];
        child.getPath()[child.getPath().size() - 1] = parent1.getPath().back();

        // determine a random interval of genes to be inherited
        unsigned int startIdx = 1 + rand_.nextInt((parent1.getPath().size() - 2) / 2);
        unsigned int length = 1 + rand_.nextInt(parent1.getPath().size() - startIdx - 2);

        // apply genes from parent1
        for(unsigned int i = 0; i < length; ++i) {
            unsigned int idx = i + startIdx;
            int node = parent1.getPath()[idx];
            childGeneInUse_[idx] = true;
            child.getPath()[idx] = node;
            graphNodeInUse_[node] = true;
        }

        // apply remaining genes from parent2
        unsigned int childIdx = 0;
        for(unsigned int i = 0; i < parent2.getPath().size(); ++i) {
            int node =  parent2.getPath()[i];
            // check if this node was already used
            if(graphNodeInUse_[node])
                continue;

            // find index to insert the gene
            while(childIdx < childGeneInUse_.size() && childGeneInUse_[childIdx])
                ++childIdx;

            childGeneInUse_[childIdx] = true;
            child.getPath()[childIdx] = node;
        }
    }
}

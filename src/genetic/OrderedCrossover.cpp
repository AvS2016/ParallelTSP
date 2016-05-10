#include <cassert>
#include <random>
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
        individualGene_.resize(size);
        populationGene_.resize(size);
        for (unsigned int i = 0; i < individualGene_.size(); ++i)
        {
            individualGene_[i] = false;
            populationGene_[i] = false;
        }

        individualGene_[0] = true;
        individualGene_[individualGene_.size()-1] = true;
        populationGene_[start] = true;
    }

    void OrderedCrossover::cross(Individual &parent1, Individual &parent2, Individual &child)
    {
        assert(parent1.getPath().size() == parent2.getPath().size());

        child.getPath().resize(parent1.getPath().size());
        initGeneTracker(parent1.getPath().size(), parent1.getPath()[0]);

        // set child start / end node
        child.getPath()[0] = parent1.getPath()[0];
        child.getPath()[child.getPath().size()-1] = parent1.getPath().back();

        unsigned int added = 0;
        unsigned int toAdd = parent1.getPath().size() / 2;
        while (added < toAdd)
        {
            int idx = std::rand() % parent1.getPath().size();
            if (!individualGene_[idx])
            {
                ++added;
                individualGene_[idx] = true;
                populationGene_[parent1.getPath()[idx]] = true;
                child.getPath()[idx] = parent1.getPath()[idx];
            }
        }

        added = 0;
        for (unsigned int i = 0; i < parent2.getPath().size(); ++i)
        {
            int node =  parent2.getPath()[i];
            // check if this node was already used
            if(populationGene_[node])
                continue;

            // find index to insert the gene
            while(added < individualGene_.size() && individualGene_[added])
                ++added;

            individualGene_[added] = true;
            child.getPath()[added] = node;
        }
    }
}

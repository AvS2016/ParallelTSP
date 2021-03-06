#include "RandomPopulationGenerator.hpp"

#include "utils/Random.hpp"

namespace tsp
{

    RandomPopulationGenerator::RandomPopulationGenerator(const Graph &graph)
        : graph_(graph), startNode_(0)
    {
    }

    RandomPopulationGenerator::~RandomPopulationGenerator()
    {
    }

    void RandomPopulationGenerator::setStartNode(const unsigned int startNode)
    {
        startNode_ = startNode;
    }

    void RandomPopulationGenerator::generateIndividual(Individual &individual)
    {
        if(graph_.size() == 0) {
            individual.getPath().clear();
            return;
        }

        std::vector<bool> visited(graph_.size());
        for(unsigned int i = 0; i < visited.size(); ++i)
            visited[i] = false;

        // prepare individual
        individual.getPath().resize(graph_.size() + 1);
        individual.getPath()[0] = startNode_;
        visited[startNode_] = true;

        // generate path with random nodes
        unsigned int pathIdx = 1;
        while(pathIdx + 1 < graph_.size()) {
            int node = Random::nextInt(graph_.size());
            if(!visited[node]) {
                visited[node] = true;
                individual.getPath()[pathIdx] = node;
                ++pathIdx;
            }
        }

        // find last remaining node
        for(unsigned int i = 0; i < visited.size(); ++i) {
            if(!visited[i]) {
                individual.getPath()[pathIdx] = i;
                ++pathIdx;
                break;
            }
        }

        // end node = start node
        individual.getPath()[pathIdx] = startNode_;
    }

    void RandomPopulationGenerator::generatePopulation(Population &population,
            const unsigned int size)
    {
        population.getIndividuals().resize(size);
        for(Individual &ind : population.getIndividuals())
            generateIndividual(ind);
    }

}

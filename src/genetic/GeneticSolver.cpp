#include <random>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "GeneticSolver.hpp"
#include "data/PathVerifier.hpp"

namespace tsp
{

    static double drand()
    {
        return static_cast<double>(std::rand()) /  static_cast<double>(RAND_MAX);
    }

    static double nodeDistance(const Node& n1, const Node &n2)
    {
        double dx = n1.x() - n2.x();
        double dy = n1.y() - n2.y();
        return sqrt(dx * dx + dy * dy);
    }

    static bool lessNormalizedFitness(const Individual &i1, const Individual &i2)
    {
        return i1.getNormalizedFitness() < i2.getNormalizedFitness();
    }


    GeneticSolver::GeneticSolver(const Graph& graph)
    :graph_(graph), settings_(), currPopulation_(new Population()), nextPopulation_(new Population()), crossover_(), populationGen_(graph), mutator_()
    {

    }

    GeneticSolver::~GeneticSolver()
    {
        delete nextPopulation_;
        delete currPopulation_;
    }

    void GeneticSolver::updateFitness()
    {
        // calculate distance and find maximum
        double maxDistance = 0;
        for(Individual &ind : currPopulation_->getIndividuals())
        {
            assert(PathVerifier::verify(graph_, ind.getPath()));

            double accumDistance = 0;
            for(unsigned int i = 0; i + 1 < ind.getPath().size(); ++i)
            {
                Node curr = graph_[ind.getPath()[i]];
                Node next = graph_[ind.getPath()[i+1]];
                accumDistance += nodeDistance(curr, next);
            }
            ind.setDistance(accumDistance);
            if (accumDistance > maxDistance)
                maxDistance = accumDistance;
        }

        // calc fitness relative to maximum distance (shorter = greater fitness)
        double fitnessSum = 0;
        for(Individual &ind : currPopulation_->getIndividuals())
        {
            double fitness = maxDistance / ind.getDistance();
            fitness = fitness * fitness;
            ind.setFitness(fitness);
            fitnessSum += ind.getFitness();
        }

        // calc normalized fitness
        for(Individual &ind : currPopulation_->getIndividuals())
            ind.setNormalizedFitness(ind.getFitness() / fitnessSum);

        // sort descending to fitness
        std::sort(currPopulation_->getIndividuals().begin(),
                currPopulation_->getIndividuals().end(),
                lessNormalizedFitness);

        for (Individual &ind : currPopulation_->getIndividuals())
            std::cout << ind.getFitness() << ",";
        std::cout << "\n";
    }

    void GeneticSolver::select()
    {
        unsigned int parentCount = 0;
        while(parentCount < parents_.size())
        {
            // generate target fitness value
            double selectFitness = drand();
            double accumFitness = 0;
            for (unsigned int i = 0; i < currPopulation_->getIndividuals().size(); ++i)
            {
                // calculated accumulated fitness
                accumFitness += currPopulation_->getIndividuals()[i].getNormalizedFitness();
                // check if random fitness is in interval
                if (accumFitness >= selectFitness)
                {
                    // check if previous parent was same
                    if(parentCount % 2 == 1 && parents_[parentCount-1] == static_cast<int>(i))
                        continue;
                    parents_[parentCount] = i;
                    ++parentCount;
                    break;
                }
            }
        }
    }

    void GeneticSolver::crossover()
    {
        assert(currPopulation_->getIndividuals().size() % 2 == 0);
        assert((currPopulation_->getIndividuals().size() / 2) % 2 == 0);

        for (unsigned int i = 0; i < parents_.size(); i += 2)
        {
            int p1 = parents_[i];
            int p2 = parents_[i+1];

            assert(PathVerifier::verify(graph_, currPopulation_->getIndividuals()[p1].getPath()));
            assert(PathVerifier::verify(graph_, currPopulation_->getIndividuals()[p2].getPath()));

            int c = i / 2;

            crossover_.cross(currPopulation_->getIndividuals()[p1],
                    currPopulation_->getIndividuals()[p2],
                    nextPopulation_->getIndividuals()[c]);

            assert(PathVerifier::verify(graph_, currPopulation_->getIndividuals()[c].getPath()));
        }
    }

    void GeneticSolver::mutate()
    {
        for (unsigned int i = 0; i < nextPopulation_->getIndividuals().size(); ++i)
        {
            double shouldMutate = drand();
            if (shouldMutate <= settings_.mutationChance)
                mutator_.mutate(currPopulation_->getIndividuals()[i]);
        }
    }

    void GeneticSolver::setSettings(const Settings& settings)
    {
        settings_ = settings;
        populationGen_.setStartNode(settings_.startNode);
    }

    void GeneticSolver::init()
    {
        populationGen_.generatePopulation(*currPopulation_, settings_.populationSize);
        nextPopulation_->getIndividuals().resize(settings_.populationSize);
        parents_.resize(settings_.populationSize * 2);
        updateFitness();
    }

    void GeneticSolver::nextGeneration()
    {
        std::cout << "select\n";
        select();
        std::cout << "crossover\n";
        crossover();
        std::cout << "mutate\n";
        mutate();
        std::cout << "swap\n";

        Population *tmp = currPopulation_;
        currPopulation_ = nextPopulation_;
        nextPopulation_ = tmp;

        std::cout << "update fitness\n";
        updateFitness();
        std::cout << "done\n";
    }

    Individual &GeneticSolver::getBest()
    {
        return currPopulation_->getIndividuals().back();
    }

    Population &GeneticSolver::getPopulation()
    {
        return *currPopulation_;
    }

}

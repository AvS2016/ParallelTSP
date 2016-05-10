#include <random>
#include <cassert>
#include <algorithm>
#include <iostream>
#include "GeneticSolver.hpp"
#include "data/PathVerifier.hpp"

namespace tsp
{

    static double nodeDistance(const Node& n1, const Node &n2)
    {
        double dx = n1.x() - n2.x();
        double dy = n1.y() - n2.y();
        return sqrt(dx * dx + dy * dy);
    }

    static bool lessFitness(const Individual &i1, const Individual &i2)
    {
        return i1.getNormalizedFitess() > i2.getNormalizedFitess();
    }


    GeneticSolver::GeneticSolver(const Graph& graph)
    :graph_(graph), settings_(), currPopulation_(new Population()), nextPopulation_(new Population()), crossover_(), populationGen_(graph), mutator_()
    {

    }

    GeneticSolver::~GeneticSolver()
    {
    }

    void GeneticSolver::updateFitness()
    {
        // calc fitness
        double fitnessSum = 0;
        for(Individual &ind : currPopulation_->getIndividuals())
        {
            assert(PathVerifier::verify(graph_, ind.getPath()));

            double sum = 0;
            for(unsigned int i = 0; i + 1 < ind.getPath().size(); ++i)
            {
                Node curr = graph_[ind.getPath()[i]];
                Node next = graph_[ind.getPath()[i+1]];
                sum += nodeDistance(curr, next);
            }
            ind.setFitness(1 / sum);
            fitnessSum += ind.getFitness();
        }
        // calc normalized fitness
        for(Individual &ind : currPopulation_->getIndividuals())
        {
            ind.setNormalizedFitness(ind.getFitness() / fitnessSum);
        }

        // sort descending to fitness
        std::sort(currPopulation_->getIndividuals().begin(), currPopulation_->getIndividuals().end(), lessFitness);
    }

    void GeneticSolver::select()
    {
        unsigned int selIndividuals = 0;
        while(selIndividuals < parents_.size())
        {
            double fit = static_cast<double>(std::rand() % 1000000) / 1000000.0;
            double sum = 0;
            for (unsigned int i = 0; i < currPopulation_->getIndividuals().size(); ++i)
            {
                // calculated accumulated value and check if is fit enough
                sum += currPopulation_->getIndividuals()[i].getNormalizedFitess();
                if (sum >= fit)
                {
                    // check if previous parent was same
                    if(selIndividuals % 2 == 1 && parents_[selIndividuals-1] == static_cast<int>(i))
                        continue;
                    parents_[selIndividuals] = i;
                    ++selIndividuals;
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
        unsigned int mutations = static_cast<unsigned int>((nextPopulation_->getIndividuals().size()) * settings_.mutationChance);
        for (unsigned int i = 0; i < mutations; ++i)
        {
            unsigned int idx = std::rand() % nextPopulation_->getIndividuals().size();
            mutator_.mutate(currPopulation_->getIndividuals()[idx]);
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
        return currPopulation_->getIndividuals().front();
    }

    Population &GeneticSolver::getPopulation()
    {
        return *currPopulation_;
    }

}

#include <random>
#include <cassert>
#include <algorithm>
#include "GeneticSolver.hpp"

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
    :graph_(graph), settings_(), crossover_(), populationGen_(graph), mutator_()
    {

    }

    GeneticSolver::~GeneticSolver()
    {
    }

    void GeneticSolver::updateFitness()
    {
        // calc fitness
        double fitnessSum = 0;
        for(Individual &ind : population_.getIndividuals())
        {
            double sum = 0;
            for(unsigned int i = 0; i + 1 < ind.getPath().size(); ++i)
            {
                Node curr = graph_[ind.getPath()[i]];
                Node next = graph_[ind.getPath()[i+1]];
                sum += nodeDistance(curr, next);
            }
            ind.setFitness(sum);
            fitnessSum += sum;
        }
        // calc normalized fitness
        for(Individual &ind : population_.getIndividuals())
        {
            ind.setNormalizedFitness(ind.getFitness() / fitnessSum);
        }

        // sort descending to fitness
        std::sort(population_.getIndividuals().begin(), population_.getIndividuals().end(), lessFitness);
    }

    void GeneticSolver::select()
    {
        assert(reproductionStates_.size() == population_.getIndividuals().size());

        for (unsigned int i = 0; i < reproductionStates_.size(); ++i)
            reproductionStates_[i] = DEAD;

        unsigned int selIndividuals = 0;
        while(selIndividuals < population_.getIndividuals().size() / 2)
        {
            double fit = static_cast<double>(std::rand() % 1000000) / 1000000.0;
            double sum = 0;
            for (unsigned int i = 0; i < reproductionStates_.size(); ++i)
            {
                // calculated accumulated value and check if is fit enough
                sum += population_.getIndividuals()[i].getNormalizedFitess();
                if (sum >= fit && reproductionStates_[i] != SELECTED)
                {
                    reproductionStates_[i] = SELECTED;
                    ++selIndividuals;
                    break;
                }
            }
        }

    }

    unsigned int GeneticSolver::findParent()
    {
        int randRet = std::rand() % reproductionStates_.size();

        for (unsigned int i = 0; i < reproductionStates_.size(); ++i)
        {
            unsigned int idx = (randRet + i) % reproductionStates_.size();
            if(reproductionStates_[idx] == SELECTED)
                return idx;
        }

        assert(false);
        return -1;
    }

    unsigned int GeneticSolver::findChild()
    {
        for (unsigned int i = 0; i < reproductionStates_.size(); ++i)
            if (reproductionStates_[i] == DEAD)
                return i;

        assert(false);
        return 0;
    }

    void GeneticSolver::crossover()
    {
        assert(population_.getIndividuals().size() % 2 == 0);
        assert((population_.getIndividuals().size() / 2) % 2 == 0);

        for (unsigned int i = 0; i < population_.getIndividuals().size() / 2; i += 2)
        {
            int p1 = findParent();
            reproductionStates_[p1] = CROSSED;
            int p2 = findParent();
            reproductionStates_[p2] = CROSSED;

            int c1 = findChild();
            reproductionStates_[c1] = BREEDED;
            int c2 = findChild();
            reproductionStates_[c2] = BREEDED;

            crossover_.cross(population_.getIndividuals()[p1],
                    population_.getIndividuals()[p2],
                    population_.getIndividuals()[c1]);
            crossover_.cross(population_.getIndividuals()[p1],
                            population_.getIndividuals()[p2],
                            population_.getIndividuals()[c2]);
        }
    }

    unsigned int GeneticSolver::findMutant()
    {
        int randRet = std::rand() % reproductionStates_.size();
        for (unsigned int i = 0; i < reproductionStates_.size(); ++i)
        {
            unsigned int idx = (randRet + i) % reproductionStates_.size();
            if(reproductionStates_[idx] == BREEDED)
                return idx;
        }
        assert(false);
        return -1;
    }

    void GeneticSolver::mutate()
    {
        unsigned int mutations = static_cast<unsigned int>((population_.getIndividuals().size() / 2 ) * settings_.mutationChance);
        for (unsigned int i = 0; i < mutations; ++i)
        {
            unsigned int idx = findMutant();
            reproductionStates_[idx] = MUTATED;
            mutator_.mutate(population_.getIndividuals()[idx]);
        }
    }

    void GeneticSolver::setSettings(const Settings& settings)
    {
        settings_ = settings;
        populationGen_.setStartNode(settings_.startNode);
    }

    void GeneticSolver::init()
    {
        populationGen_.generatePopulation(population_, settings_.populationSize);
        reproductionStates_.resize(population_.getIndividuals().size());
        updateFitness();
    }

    void GeneticSolver::nextGeneration()
    {
        select();
        crossover();
        mutate();
        updateFitness();
    }

    Individual &GeneticSolver::getBest()
    {
        return population_.getIndividuals().back();
    }

    Population &GeneticSolver::getPopulation()
    {
        return population_;
    }

}

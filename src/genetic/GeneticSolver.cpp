#include <cassert>
#include "GeneticSolver.hpp"
#include "data/PathVerifier.hpp"
#include "utils/Random.hpp"

namespace tsp
{

    GeneticSolver::GeneticSolver(const Graph &graph)
        : graph_(graph), settings_(), currPopulation_(new Population()),
          nextPopulation_(new Population()),
          fitnessUpdater_(graph), selector_(graph), crossover_(), populationGen_(graph),
          mutator_(), eliteCount_(0)
    {

    }

    GeneticSolver::~GeneticSolver()
    {
        delete nextPopulation_;
        delete currPopulation_;
    }

    void GeneticSolver::setSettings(const Settings &settings)
    {
        settings_ = settings;
        populationGen_.setStartNode(settings_.startNode);
    }

    void GeneticSolver::init()
    {
        eliteCount_ = static_cast<unsigned int>(settings_.elitismRate * settings_.populationSize);

        fitnessUpdater_.setFitnessPow(settings_.fitnessPow);
        populationGen_.generatePopulation(*currPopulation_, settings_.populationSize);
        nextPopulation_->getIndividuals().resize(settings_.populationSize);
        parents_.resize((settings_.populationSize - eliteCount_) * 2);

        updateFitness();
    }

    void GeneticSolver::updateFitness()
    {
        fitnessUpdater_.update(*currPopulation_);
    }

    void GeneticSolver::select()
    {
        selector_.select(*currPopulation_, parents_);
    }

    void GeneticSolver::applyElite()
    {
        assert(eliteCount_ < currPopulation_->getIndividuals().size());
        for(unsigned int i = 0; i < eliteCount_; ++i) {
            // best individuals are in the back
            unsigned int idx = currPopulation_->getIndividuals().size() - i - 1;
            nextPopulation_->getIndividuals()[idx] = currPopulation_->getIndividuals()[idx];
        }
    }

    void GeneticSolver::crossover()
    {
        for(unsigned int i = 0; i < parents_.size(); i += 2) {
            int p1 = parents_[i];
            int p2 = parents_[i + 1];
            int c = i / 2;

            // assert parents are valid
            assert(PathVerifier::verify(graph_,
                                        currPopulation_->getIndividuals()[p1].getPath()));
            assert(PathVerifier::verify(graph_,
                                        currPopulation_->getIndividuals()[p2].getPath()));

            crossover_.cross(currPopulation_->getIndividuals()[p1],
                             currPopulation_->getIndividuals()[p2],
                             nextPopulation_->getIndividuals()[c]);

            // assert new child is valid
            assert(PathVerifier::verify(graph_,
                                        currPopulation_->getIndividuals()[c].getPath()));
        }
    }

    void GeneticSolver::mutate()
    {
        for(unsigned int i = 0; i < nextPopulation_->getIndividuals().size(); ++i) {
            double shouldMutate = Random::nextDouble();
            if(shouldMutate <= settings_.mutationChance)
                mutator_.mutate(currPopulation_->getIndividuals()[i]);
        }
    }

    void GeneticSolver::swapPopulations()
    {
        Population *tmp = currPopulation_;
        currPopulation_ = nextPopulation_;
        nextPopulation_ = tmp;
    }

    void GeneticSolver::nextGeneration()
    {
        select();
        applyElite();
        crossover();
        mutate();
        swapPopulations();
        updateFitness();
    }

    Population &GeneticSolver::getPopulation()
    {
        return *currPopulation_;
    }

}

#include "PopulationExchanger.hpp"
#include <boost/serialization/vector.hpp>
#include <boost/mpi.hpp>
#include <net/BoostConfigSerializer.hpp>
#include <cassert>
#include <iostream>
#include "utils/Random.hpp"

#define TAG 0
#define MASTER_RANK 0

namespace tsp
{

    PopulationExchanger::PopulationExchanger(int argc, char **argv)
        : env_(argc, argv), world_(), exchangeCount_(0), rank_(0), src_(0), dest_(0)
    {
    }

    PopulationExchanger::~PopulationExchanger()
    {
    }

    void PopulationExchanger::exchangePopulation(Population &p)
    {
        assert(world_.size() % 2 == 0);

        rank_ = world_.rank();
        dest_ = (rank_ + 1) % world_.size();
        src_ = (rank_ - 1) % world_.size();

        sentIndividualsIdx_.resize(exchangeCount_);
        sentIndividuals_.resize(exchangeCount_);
        receivedIndividuals_.resize(exchangeCount_);
        used_.resize(p.getIndividuals().size());

        // init vectors
        for(unsigned int i = 0; i < used_.size(); ++i)
            used_[i] = false;

        // prepare rnd individuals to send
        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            int index;
            do {
                index = Random::nextInt(p.getIndividuals().size());
            } while(used_[index]);

            sentIndividualsIdx_[i] = index;
            sentIndividuals_[i] = p.getIndividuals()[index].getPath();
            used_[index] = true;
        }

        if(rank_ % 2 == 0) {
            sendIndividuals();
            recvIndividuals();
        } else {
            recvIndividuals();
            sendIndividuals();
        }

        // Replace old with new individuals
        for(unsigned int i = 0; i < exchangeCount_; ++i)
            p.getIndividuals()[sentIndividualsIdx_[i]].getPath() = receivedIndividuals_[i];
    }

    void PopulationExchanger::sendIndividuals()
    {
        world_.send(dest_, TAG, sentIndividuals_);
    }

    void PopulationExchanger::recvIndividuals()
    {
        world_.recv(src_, TAG, receivedIndividuals_);
    }

    void PopulationExchanger::gatherPopulation(Population &p)
    {
        // 0 is main collector
        if(isMaster()) {
            std::vector<Path> bestIndividuals;
            boost::mpi::gather(world_, p.getBestIndividual().getPath(), bestIndividuals,
                               MASTER_RANK);

            p.getIndividuals().resize(bestIndividuals.size());
            // overwrite current population with best individuals
            for(unsigned int i = 0; i < bestIndividuals.size(); ++i)
                p.getIndividuals()[i].setPath(bestIndividuals[i]);

        } else {
            boost::mpi::gather(world_, p.getBestIndividual().getPath(), MASTER_RANK);
        }
    }

    void PopulationExchanger::broadcastConfig(Config &cfg)
    {
        boost::mpi::broadcast(world_, cfg, MASTER_RANK);
    }

    bool PopulationExchanger::broadcastTermCond(const bool cond)
    {
        bool result = cond;
        boost::mpi::broadcast(world_, result, MASTER_RANK);
        return result;
    }

    void PopulationExchanger::gatherDistPerGen(std::vector<double> &distPerGen,
            std::vector<std::vector<double>> &result)
    {
        if(isMaster()) {
            boost::mpi::gather(world_, distPerGen, result, MASTER_RANK);
        } else {
            boost::mpi::gather(world_, distPerGen, MASTER_RANK);
        }
    }

    void PopulationExchanger::setExchangeCount(unsigned int count)
    {
        exchangeCount_ = count;
    }

    bool PopulationExchanger::isMaster() const
    {
        return world_.rank() == MASTER_RANK;
    }

    int PopulationExchanger::getRank() const
    {
        return world_.rank();
    }



}

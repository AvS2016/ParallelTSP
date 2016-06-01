#include "PopulationExchanger.hpp"
#include <boost/serialization/vector.hpp>
#include <boost/mpi.hpp>
#include <net/BoostConfigSerializer.hpp>
#include <cassert>
#include <iostream>
#include "utils/Random.hpp"
#define TAG 0

namespace tsp
{

    PopulationExchanger::PopulationExchanger(int argc, char **argv)
        : env_(argc, argv), world_(), exchangeCount_(0), rank_(0), src_(0), dest_(0)
    {
    }

    PopulationExchanger::~PopulationExchanger()
    {
    }

    void PopulationExchanger::exchange(Population &p)
    {
        assert(world_.size() % 2 == 0);

        rank_ = world_.rank();
        dest_ = (rank_ + 1) % world_.size();
        src_ = (rank_ - 1) % world_.size();

        toSend_.resize(exchangeCount_);
        used_.resize(p.getIndividuals().size());
        received_.resize(exchangeCount_);

        // init vectors
        for(unsigned int i = 0; i < used_.size(); ++i)
            used_[i] = false;
        for(unsigned int i = 0; i < received_.size(); ++i)
            received_[i].resize(p.getIndividuals().size() + 1);

        // prepare rnd individuals to send
        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            int index;
            do {
                index = Random::nextInt(p.getIndividuals().size());
            } while(used_[index]);

            toSend_[i] = index;
            used_[index] = true;
        }

        if(rank_ % 2 == 0) {
            sendIndividuals(p);
            recvIndividuals();
        } else {
            recvIndividuals();
            sendIndividuals(p);
        }

        // Replace old with new individuals
        for(unsigned int i = 0; i < exchangeCount_; ++i)
            p.getIndividuals()[toSend_[i]].getPath() = received_[i];
    }

    void PopulationExchanger::sendIndividuals(Population &p)
    {
        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            world_.send(dest_, TAG, p.getIndividuals()[toSend_[i]].getPath());
        }

    }

    void PopulationExchanger::recvIndividuals()
    {
        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            world_.recv(src_, TAG, received_[i]);
        }
    }

    void PopulationExchanger::gather(Population &p)
    {
        // 0 is main collector
        if(isMaster()) {
            std::vector<Path> bestIndividuals;
            boost::mpi::gather(world_, p.getBestIndividual().getPath(), bestIndividuals, 0);

            // overwrite current pupulation with best individuals.. dont need them anymore
            for(unsigned int i = 0; i < bestIndividuals.size(); ++i) {
                std::cout << "-- Process " << i << " reported " << pathToStr(
                              bestIndividuals[i]) << "\n";
                p.getIndividuals()[i].getPath() = bestIndividuals[i];
            }

        } else {
            boost::mpi::gather(world_, p.getBestIndividual().getPath(), 0);
        }


    }

    void PopulationExchanger::exchangeConfig(Config &cfg)
    {
        boost::mpi::broadcast(world_, cfg, 0);
    }

    void PopulationExchanger::setExchangeCount(unsigned int count)
    {
        exchangeCount_ = count;
    }

    bool PopulationExchanger::isMaster() const
    {
        return world_.rank() == 0;
    }

    int PopulationExchanger::getRank() const
    {
        return world_.rank();
    }



}

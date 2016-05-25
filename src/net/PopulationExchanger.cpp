/*
 * PopulationExchanger.cpp
 *
 *  Created on: 25.05.2016
 *      Author: user
 */

#include "PopulationExchanger.hpp"
#include "utils/Random.hpp"
#include <boost/serialization/vector.hpp>
#define TAG 0

namespace tsp
{

    PopulationExchanger::PopulationExchanger(int argc, char **argv)
        : env_(argc, argv), world_(), exchangeCount_(0)
    {
    }

    PopulationExchanger::~PopulationExchanger()
    {
    }

    void PopulationExchanger::exchange(Population &p)
    {

        int rank = world_.rank();
        int target = (rank + 1) % world_.size();
        int src = (rank - 1) % world_.size();

        std::vector<unsigned int> toSend(exchangeCount_);
        std::vector<bool> used(p.getIndividuals().size());

        // prepare rnd individuals to send
        for(unsigned int i = 0; i < exchangeCount_; ++i) { // save 1 register - Hi Mark
            int index;
            do {
                index = Random::nextInt(p.getIndividuals().size());
            } while(used[index]);

            toSend[i] = index;
            used[index] = true;
        }


        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            world_.send(target, TAG, p.getIndividuals()[toSend[i]].getPath());
        }

        std::vector<Path> received(exchangeCount_);
        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            world_.recv(src, TAG, received[i]);
        }

        // Replace old with new individuals
        for(unsigned int i = 0; i < exchangeCount_; ++i) {
            p.getIndividuals()[toSend[i]].getPath() = received[i];
        }


    }

    void PopulationExchanger::setExchangeCount(unsigned int count)
    {
        exchangeCount_ = count;
    }

} /* namespace tsp */

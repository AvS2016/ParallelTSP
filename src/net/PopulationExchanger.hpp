#ifndef NET_POPULATIONEXCHANGER_HPP_
#define NET_POPULATIONEXCHANGER_HPP_

// external libs
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>

// internal libs
#include "genetic/Population.hpp"
#include "data/Config.hpp"

namespace tsp
{

    class PopulationExchanger
    {
    private:
        boost::mpi::environment env_;
        boost::mpi::communicator world_;
        unsigned int exchangeCount_;
        int rank_;
        int src_;
        int dest_;
        std::vector<unsigned int> toSend_;
        std::vector<bool> used_;
        std::vector<Path> received_;

        void sendIndividuals(Population &p);
        void recvIndividuals();
    public:
        PopulationExchanger(int argc, char **argv);
        ~PopulationExchanger();

        void exchange(Population &p);
        void gather(Population &p);
        void exchangeConfig(Config &cfg);
        bool broadcastTermCond(const bool cond);
        void setExchangeCount(unsigned int count);
        bool isMaster() const;
        int getRank() const;
    };

}

#endif

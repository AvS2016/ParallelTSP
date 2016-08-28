#ifndef NET_POPULATIONEXCHANGER_HPP_
#define NET_POPULATIONEXCHANGER_HPP_

#include <vector>
#include <boost/mpi/environment.hpp>
#include <boost/mpi/communicator.hpp>
#include "genetic/Population.hpp"
#include "data/Config.hpp"
#include "data/Statistics.hpp"

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
        std::vector<unsigned int> sentIndividualsIdx_;
        std::vector<bool> used_;
        std::vector<Path> receivedIndividuals_;
        std::vector<Path> sentIndividuals_;

        void sendIndividuals(Population &p);
        void recvIndividuals();
    public:
        PopulationExchanger(int argc, char **argv);
        ~PopulationExchanger();

        void exchangePopulation(Population &p);
        void gatherPopulation(Population &p);
        void broadcastConfig(Config &cfg);
        bool broadcastTermCond(const bool cond);
        void gatherDistPerGen(std::vector<double> &distPerGen, std::vector<std::vector<double>> &result);
        void setExchangeCount(unsigned int count);
        bool isMaster() const;
        int getRank() const;
    };

}

#endif

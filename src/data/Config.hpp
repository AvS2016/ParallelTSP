#ifndef DATA_CONFIG_HPP_
#define DATA_CONFIG_HPP_

#include "genetic/GeneticSolver.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>

namespace tsp
{
    enum TerminateType {
        GENERATIONS = 0,
        TIME
    };

    struct Config {
        std::string graphFile;
        std::string pathFile;
        GeneticSolver::Settings gaSettings;
        double exchangeRate;
        TerminateType terminateType;
        unsigned int generationCount;
        boost::posix_time::time_duration duration;
    };

}

#endif

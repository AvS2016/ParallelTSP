#ifndef DATA_CONFIG_HPP_
#define DATA_CONFIG_HPP_

#include "genetic/GeneticSolver.hpp"

namespace tsp
{
    struct Config
    {
        unsigned int generationCount;
        std::string graphFile;
        std::string pathFile;
        GeneticSolver::Settings gaSettings;
    };

}

#endif

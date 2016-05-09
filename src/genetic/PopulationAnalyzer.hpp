#ifndef GENETIC_POPULATIONANALYZER_HPP_
#define GENETIC_POPULATIONANALYZER_HPP_

#include "genetic/Population.hpp"

namespace tsp
{
    class PopulationAnalyzer
    {
    private:
        PopulationAnalyzer();
        ~PopulationAnalyzer();
    public:

        static double getMeanFitness(Population &population);

    };

}

#endif

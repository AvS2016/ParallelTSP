#include <genetic/PopulationAnalyzer.hpp>

namespace tsp
{

    PopulationAnalyzer::PopulationAnalyzer()
    {

    }

    PopulationAnalyzer::~PopulationAnalyzer()
    {
    }

    double PopulationAnalyzer::getMeanFitness(Population& population)
    {
        double sum = 0;
        for (Individual &ind: population.getIndividuals())
            sum += ind.getFitness();

        return sum / population.getIndividuals().size();
    }

    double PopulationAnalyzer::getMeanDistance(Population& population)
    {
        double sum = 0;
        for (Individual &ind: population.getIndividuals())
            sum += ind.getDistance();

        return sum / population.getIndividuals().size();
    }

}

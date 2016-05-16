#include <catch.hpp>
#include "genetic/FitnessUpdater.hpp"

using namespace tsp;

static bool doubleEqual(double a, double b)
{
    double diff = std::abs(a - b);
    return diff <= 0.001;
}

TEST_CASE("FitnessUpdater")
{
    SECTION("should handle regular population")
    {
        Graph g = {
            Node(0,0,0),
            Node(1,1,0),
            Node(2,1,1),
            Node(3,0,1)
        };

        FitnessUpdater fu(g);
        Population pop;
        // 12.828427125
        pop.getIndividuals().resize(3);
        pop.getIndividuals()[0].getPath() = {0,1,2,3,0}; // dist: 4          , fitness: 1.457106781
        pop.getIndividuals()[1].getPath() = {0,2,3,1,0}; // dist: 4.828427125, fitness: 1
        pop.getIndividuals()[2].getPath() = {0,3,2,1,0}; // dist: 4          , fitness: 1.457106781

        for(Individual &i : pop.getIndividuals())
        {
            REQUIRE(i.getDistance() == 0);
            REQUIRE(i.getFitness() == 0);
            REQUIRE(i.getNormalizedFitness() == 0);
        }

        fu.update(pop);

        // check if sorted, greatest dist to lowest
        REQUIRE(doubleEqual(pop.getIndividuals()[0].getDistance(),4.828427125));
        REQUIRE(doubleEqual(pop.getIndividuals()[1].getDistance(),4));
        REQUIRE(doubleEqual(pop.getIndividuals()[2].getDistance(),4));

        // check if fitness is correct
        // REQUIRE(doubleEqual(pop.getIndividuals()[0].getFitness(),1));
        // REQUIRE(doubleEqual(pop.getIndividuals()[1].getFitness(),1.457106781));
        // REQUIRE(doubleEqual(pop.getIndividuals()[2].getFitness(),1.457106781));

        // check if normalized fitness sums up to 1
        double sum = 0;
        for(Individual &i : pop.getIndividuals())
            sum += i.getNormalizedFitness();
        REQUIRE(doubleEqual(sum, 1));
    }

    SECTION("should handle empty population")
    {
        Graph g = {
            Node(0,0,0),
            Node(1,1,0),
            Node(2,1,1),
            Node(3,0,1)
        };

        FitnessUpdater fu(g);
        Population pop;

        fu.update(pop);

        REQUIRE(pop.getIndividuals().size() == 0);
    }
}

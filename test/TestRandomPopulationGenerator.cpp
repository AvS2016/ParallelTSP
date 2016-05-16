#include <catch.hpp>
#include "genetic/RandomPopulationGenerator.hpp"
#include "data/PathVerifier.hpp"

using namespace tsp;

TEST_CASE("RandomPopulationGenerator")
{
    Graph g = {
        Node(0,0,0),
        Node(1,1,2),
        Node(2,0,3),
        Node(3,2,0),
        Node(4,3,1),
        Node(5,2,2),
    };

    SECTION("should generate regular population")
    {
        unsigned int size = 10;
        Population pop;
        RandomPopulationGenerator rg(g);

        rg.generatePopulation(pop, size);

        REQUIRE(pop.getIndividuals().size() == size);
        for(Individual &i: pop.getIndividuals())
            REQUIRE(PathVerifier::verify(g,i.getPath()));
    }

    SECTION("should handle empty population")
    {
        unsigned int size = 0;
        Population pop;
        RandomPopulationGenerator rg(g);

        rg.generatePopulation(pop, size);

        REQUIRE(pop.getIndividuals().size() == size);
    }

    SECTION("should handle empty graph")
    {
        Graph g2;
        unsigned int size = 10;
        Population pop;
        RandomPopulationGenerator rg(g2);

        rg.generatePopulation(pop, size);

        REQUIRE(pop.getIndividuals().size() == size);
        for(Individual &i: pop.getIndividuals())
            REQUIRE(i.getPath().size() == 0);
    }
}

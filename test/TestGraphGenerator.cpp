#include <catch.hpp>
#include "generator/GraphGenerator.cpp"

using namespace tsp;

static std::string generateNodeID(int x, int y)
{
    std::stringstream ss;
    ss << x << "/" << y;
    return ss.str();
}

TEST_CASE("GraphGenerator")
{
    Graph g;
    GraphGenerator gg;

    SECTION("should generate regular graph")
    {
        unsigned int width = 20;
        unsigned int height = 10;
        unsigned int nodes = 5;

        gg.setSettings(width, height, nodes);
        gg.generate(g);

        REQUIRE(g.size() == nodes);
        for(Node &n : g)
        {
            REQUIRE(n.x() <= width);
            REQUIRE(n.y() <= height);
        }
    }

    SECTION("should generate empty graph")
    {
        unsigned int width = 10;
        unsigned int height = 10;
        unsigned int nodes = 0;

        gg.setSettings(width, height, nodes);
        gg.generate(g);

        REQUIRE(g.size() == 0);
    }

    SECTION("should generate full graph")
    {
        unsigned int width = 3;
        unsigned int height = 3;
        unsigned int nodes = 9;

        gg.setSettings(width, height, nodes);
        gg.generate(g);

        std::map<std::string, bool> exists;
        REQUIRE(g.size() == nodes);
        for(Node &n : g)
        {
            REQUIRE(n.x() <= width);
            REQUIRE(n.y() <= height);

            std::string id = generateNodeID(n.x(), n.y());
            REQUIRE(exists.find(id) == exists.end());
            exists[id] = true;
        }
    }

}

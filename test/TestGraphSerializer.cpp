#include <catch.hpp>
#include <sstream>
#include "data/GraphSerializer.hpp"

using namespace tsp;

TEST_CASE("GraphSerializer serialize")
{
    SECTION("should handle regular graph")
    {
        Graph g = {
            Node(0, 0, 0),
            Node(1, 1, 1),
            Node(2, 2, 1),
            Node(3, 1, 2),
            Node(4, 1, 0)
        };

        std::ostringstream os;

        REQUIRE(GraphSerializer::serialize(g, os));
        //TODO add REQUIRE
    }

    SECTION("should handle empty graph")
    {
        Graph g;
        std::ostringstream os;

        REQUIRE(GraphSerializer::serialize(g, os));
        //TODO add REQUIRE
    }
}


TEST_CASE("GraphSerializer deserialize")
{
    SECTION("should handle regular graph")
    {
        Graph g;
        std::stringstream ss;
        ss << "{\"nodes\":[{\"id\":0,\"x\":0,\"y\":0},{\"id\":1,\"x\":1,\"y\":0},{\"id\":2,\"x\":0,\"y\":1}]}";

        REQUIRE(GraphSerializer::deserialize(g, ss));
        REQUIRE(g.size() == 3);

        REQUIRE(g[0].id() == 0);
        REQUIRE(g[0].x() == 0);
        REQUIRE(g[0].y() == 0);

        REQUIRE(g[1].id() == 1);
        REQUIRE(g[1].x() == 1);
        REQUIRE(g[1].y() == 0);

        REQUIRE(g[2].id() == 2);
        REQUIRE(g[2].x() == 0);
        REQUIRE(g[2].y() == 1);
    }

    SECTION("should handle empty graph")
    {
        Graph g;
        std::stringstream ss;
        ss << "{\"nodes\":[]}";

        REQUIRE(GraphSerializer::deserialize(g, ss));
        REQUIRE(g.size() == 0);
    }

    SECTION("should detect invalid graph")
    {
        Graph g;
        std::stringstream ss;
        ss << "{\"nodes\":1}";

        REQUIRE_FALSE(GraphSerializer::deserialize(g, ss));
        REQUIRE(g.size() == 0);
    }

    SECTION("should detect missing element")
    {
        Graph g;
        std::stringstream ss;
        ss << "{\"foo\":[]}";

        REQUIRE_FALSE(GraphSerializer::deserialize(g, ss));
        REQUIRE(g.size() == 0);
    }

    SECTION("should detect invalid json")
    {
        Graph g;
        std::stringstream ss;
        ss << "{\"nodes\":[}";

        REQUIRE_FALSE(GraphSerializer::deserialize(g, ss));
        REQUIRE(g.size() == 0);
    }
}

#include <catch.hpp>
#include "data/PathVerifier.hpp"

using namespace tsp;

TEST_CASE("PathVerifier with regular graph")
{
    Graph g = {
        Node(0, 0, 0),
        Node(1, 1, 1),
        Node(2, 2, 1),
        Node(3, 1, 2),
        Node(4, 1, 0)
    };

    SECTION("should accept valid path")
    {
        Path p = {0,1,2,3,4,0};
        REQUIRE(PathVerifier::verify(g, p));
    }

    SECTION("should detect missing node")
    {
        // 3 is missing
        Path p = {0,1,2,4,0};
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }

    SECTION("should detect different end/start node")
    {
        Path p = {0,1,2,3,4,1};
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }

    SECTION("should detect duplicate node")
    {
        // 2 is duplicate
        Path p = {0,1,2,3,4,2,0};
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }

    SECTION("should detect out of range node")
    {
        // 5 does not exist
        Path p = {0,1,2,5,4,0};
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }

    SECTION("should handle empty path")
    {
        Path p;
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }
}

TEST_CASE("PathVerifier with single node graph")
{
    Graph g = {
        Node(0, 0, 0),
    };

    SECTION("should accept valid path")
    {
        Path p = {0, 0};
        REQUIRE(PathVerifier::verify(g, p));
    }

    SECTION("should detect duplicate")
    {
        Path p = {0, 0, 0};
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }
}

TEST_CASE("PathVerifier with empty graph")
{
    Graph g;

    SECTION("should handle non empty path")
    {
        Path p = {0, 0};
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }

    SECTION("should handle empty path")
    {
        Path p;
        REQUIRE_FALSE(PathVerifier::verify(g, p));
    }
}

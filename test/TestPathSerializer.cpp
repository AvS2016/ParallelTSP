#include <catch.hpp>
#include <sstream>
#include "data/PathSerializer.hpp"

#include <iostream>

using namespace tsp;

TEST_CASE("PathSerializer serialize")
{
    SECTION("should handle regular path")
    {
        Path p = {1,2,3,4,5};
        std::ostringstream os;
        std::stringstream expected;
        expected << "[ 1, 2, 3, 4, 5 ]\n";

        REQUIRE(PathSerializer::serialize(p, os));
        REQUIRE(os.str() == expected.str());

    }

    SECTION("should handle empty path")
    {
        Path p;
        std::ostringstream os;
        std::stringstream expected;
        expected << "[]\n";

        REQUIRE(PathSerializer::serialize(p, os));
        REQUIRE(os.str() == expected.str());
    }
}

TEST_CASE("PathSerializer deserialize")
{
    SECTION("should handle regular path")
    {
        Path p;
        std::stringstream ss;
        ss << "[1,2,3,4,5]";

        REQUIRE(PathSerializer::deserialize(p, ss));
        REQUIRE(p.size() == 5);

        REQUIRE(p[0] == 1);
        REQUIRE(p[1] == 2);
        REQUIRE(p[2] == 3);
        REQUIRE(p[3] == 4);
        REQUIRE(p[4] == 5);
    }

    SECTION("should handle empty path")
    {
        Path p;
        std::stringstream ss;
        ss << "[]";

        REQUIRE(PathSerializer::deserialize(p, ss));
        REQUIRE(p.size() == 0);
    }

    SECTION("should handle invalid path")
    {
        Path p;
        std::stringstream ss;
        ss << "\"foo\":1";

        REQUIRE_FALSE(PathSerializer::deserialize(p, ss));
        REQUIRE(p.size() == 0);
    }

    SECTION("should handle invalid json")
    {
        Path p;
        std::stringstream ss;
        ss << "[";

        REQUIRE_FALSE(PathSerializer::deserialize(p, ss));
        REQUIRE(p.size() == 0);
    }
}

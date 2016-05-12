#include <random>
#include "Random.hpp"

namespace tsp
{

    Random::Random()
    {
    }

    Random::~Random()
    {
        // TODO Auto-generated destructor stub
    }

    int Random::nextInt()
    {
        return std::rand();
    }

    int Random::nextInt(const int max)
    {
        return std::rand() % max;
    }

    int Random::nextInt(const int min, const int max)
    {
        return min + (std::rand() % (max - min));
    }

    double Random::nextFloat()
    {
        return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }

    double Random::nextDouble()
    {
        return static_cast<double>(std::rand()) / static_cast<double>(RAND_MAX);
    }

}

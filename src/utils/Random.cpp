#include "Random.hpp"
#include <random>
#include <ctime>
#include <fstream>

namespace tsp
{

	static unsigned int getRealRand()
	{
		std::ifstream is("/dev/urandom");
		unsigned int result;
		is >> result;
		return result;
	}

    void Random::shakeRNG()
    {
        std::srand(std::time(0) + getRealRand());
    }

    void Random::shakeRNG(unsigned int seed)
    {
        std::srand(seed);
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

#ifndef UTILS_RANDOM_HPP_
#define UTILS_RANDOM_HPP_

namespace tsp
{
    class Random
    {
    private:
        Random() {}
        ~Random() {}

    public:
        static void shakeRNG();
        static void shakeRNG(unsigned int seed);

        static int nextInt();
        static int nextInt(const int max);
        static int nextInt(const int min, const int max);

        static double nextFloat();
        static double nextDouble();
    };
}

#endif

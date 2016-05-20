#include "SwapMutation.hpp"

#include <random>
#include "utils/Random.hpp"

#define RAND_IDX(s) (Random::nextInt(s - 2) + 1)

namespace tsp
{

    SwapMutation::SwapMutation()
    {
    }

    SwapMutation::~SwapMutation()
    {
    }

    void SwapMutation::mutate(Individual &individual)
    {
        int idx1, idx2;
        idx1 = RAND_IDX(individual.getPath().size());
        do {
            idx2 = RAND_IDX(individual.getPath().size());
        } while(idx1 == idx2);

        int tmp = individual.getPath()[idx1];
        individual.getPath()[idx1] = individual.getPath()[idx2];
        individual.getPath()[idx2] = tmp;
    }

}

#include <random>
#include "SwapMutation.hpp"

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
        idx1 = std::rand() % individual.getPath().size();
        do
        {
            idx2 = std::rand() % individual.getPath().size();
        } while (idx1 == idx2);

        int tmp = individual.getPath()[idx1];
        individual.getPath()[idx1] = individual.getPath()[idx2];
        individual.getPath()[idx2] = tmp;
    }

}

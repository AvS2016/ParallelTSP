#ifndef GENETIC_SWAPMUTATION_HPP_
#define GENETIC_SWAPMUTATION_HPP_

#include "genetic/Individual.hpp"
#include "utils/Random.hpp"

namespace tsp
{
    class SwapMutation
    {
    private:
        Random rand_;
    public:
        SwapMutation();
        ~SwapMutation();

        void mutate(Individual &individual);
    };

}

#endif

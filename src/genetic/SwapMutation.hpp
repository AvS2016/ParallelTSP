#ifndef GENETIC_SWAPMUTATION_HPP_
#define GENETIC_SWAPMUTATION_HPP_

#include "genetic/Individual.hpp"

namespace tsp
{
    class SwapMutation
    {
    public:
        SwapMutation();
        ~SwapMutation();

        void mutate(Individual &individual);
    };

}

#endif

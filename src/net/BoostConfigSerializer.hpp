#ifndef NET_BOOSTCONFIGSERIALIZER_HPP_
#define NET_BOOSTCONFIGSERIALIZER_HPP_

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <net/BoostConfigSerializer.hpp>
#include "data/Config.hpp"

namespace boost
{
    namespace serialization
    {

        template<class Archive>
        void serialize(Archive &ar, tsp::GeneticSolver::Settings &cfg,
                       const unsigned int version)
        {
            (void) version;
            ar &cfg.elitismRate;
            ar &cfg.fitnessPow;
            ar &cfg.mutationChance;
            ar &cfg.populationSize;
            ar &cfg.startNode;
        }

        template<class Archive>
        void serialize(Archive &ar, tsp::Config &cfg, const unsigned int version)
        {
            (void) version;
            ar &cfg.exchangeRate;
            ar &cfg.gaSettings;
            ar &cfg.generationCount;
            ar &cfg.graphFile;
            ar &cfg.pathFile;
        }

    }
}

BOOST_CLASS_TRACKING(tsp::GeneticSolver::Settings, track_never);
BOOST_CLASS_VERSION(tsp::GeneticSolver::Settings, 1);

BOOST_CLASS_TRACKING(tsp::Config, track_never);
BOOST_CLASS_VERSION(tsp::Config, 1);

#endif

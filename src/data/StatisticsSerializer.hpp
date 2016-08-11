#ifndef DATA_STATISTICSSERIALIZER_HPP_
#define DATA_STATISTICSSERIALIZER_HPP_

#include <istream>
#include "data/Statistics.hpp"

namespace tsp
{

    class StatisticsSerializer
    {
    private:
        StatisticsSerializer() { }
        ~StatisticsSerializer() { }
    public:
        static bool deserialize(Statistics &stats, std::istream &is);
        static bool serialize(const Statistics &stats, std::ostream &os);
        static bool load(Statistics &stats, const std::string &file);
        static bool save(const Statistics &stats, const std::string &file);
    };

}

#endif

#ifndef DATA_STATISTICS_HPP_
#define DATA_STATISTICS_HPP_

#include <vector>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace tsp
{

    class Statistics
    {
    public:
        unsigned int genCount;
        unsigned int nodeCount;
        std::vector<double> distancePerGen;
        std::vector<boost::posix_time::time_duration> timePerGen;
        double finalDistance;
        boost::posix_time::time_duration totalTime;

        Statistics()
        :genCount(0), nodeCount(0), distancePerGen(), timePerGen(), finalDistance(0), totalTime()
        { }
        virtual ~Statistics()
        { }
    };

}

#endif

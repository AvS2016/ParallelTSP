#ifndef UTILS_STOPWATCH_HPP_
#define UTILS_STOPWATCH_HPP_

#include <boost/date_time/posix_time/posix_time.hpp>

namespace tsp
{
    bool checkDurationStr(const std::string &duration);
    boost::posix_time::time_duration durationFromStr(const std::string &duration);

    class StopWatch
    {
    private:
        bool running_;
        boost::posix_time::ptime start_;
    public:
        StopWatch();
        ~StopWatch();

        void start();
        boost::posix_time::time_duration stop();
        boost::posix_time::time_duration restart();
        boost::posix_time::time_duration interim();
    };

}

#endif

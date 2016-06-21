#include "utils/StopWatch.hpp"

namespace tsp
{
    bool checkDurationStr(const std::string &duration)
    {

        std::string numbers = "0123456789";
        char delim = ':';
        return duration.size() == 8 &&
                numbers.find(duration[0]) != std::string::npos &&
                numbers.find(duration[1]) != std::string::npos &&
                duration[2] == delim &&
                numbers.find(duration[3]) != std::string::npos &&
                numbers.find(duration[4]) != std::string::npos &&
                duration[5] == delim &&
                numbers.find(duration[6]) != std::string::npos &&
                numbers.find(duration[7]) != std::string::npos;
    }

    boost::posix_time::time_duration durationFromStr(const std::string &duration)
    {
        if(duration.size() != 8)
            return boost::posix_time::time_duration();

        int hours = std::strtol(duration.c_str(), NULL, 10);
        int minutes = std::strtol(&duration.c_str()[3], NULL, 10);
        int sec = std::strtol(&duration.c_str()[6], NULL, 10);

        return boost::posix_time::time_duration(hours, minutes, sec);
    }


    StopWatch::StopWatch()
    :running_(false), start_()
    {

    }

    StopWatch::~StopWatch()
    {
    }

    void StopWatch::start()
    {
        if(running_)
            return;

        running_ = true;
        start_ = boost::posix_time::microsec_clock::local_time();
    }

    boost::posix_time::time_duration StopWatch::stop()
    {
        if(!running_)
            return boost::posix_time::time_duration();

        running_ = false;
        return boost::posix_time::microsec_clock::local_time() - start_;
    }

    boost::posix_time::time_duration StopWatch::restart()
    {
        boost::posix_time::time_duration result = stop();
        start();
        return result;
    }

    boost::posix_time::time_duration StopWatch::interim()
    {
        if(!running_)
            return boost::posix_time::time_duration();

        return boost::posix_time::microsec_clock::local_time() - start_;
    }

}

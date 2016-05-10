#ifndef DATA_PATH_HPP_
#define DATA_PATH_HPP_

#include <sstream>
#include <vector>

namespace tsp
{
    typedef std::vector<int> Path;

    inline std::string pathToStr(const Path& p)
    {
        std::stringstream ss;
        for (unsigned int i = 0; i < p.size(); ++i)
            ss << p[i] << ",";

        return ss.str();
    }
}

#endif

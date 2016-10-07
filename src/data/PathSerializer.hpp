#ifndef DATA_PATHSERIALIZER_HPP_
#define DATA_PATHSERIALIZER_HPP_

#include <istream>
#include "data/Path.hpp"

namespace tsp
{
    class PathSerializer
    {
    private:
        PathSerializer()
        {
        }
        ~PathSerializer()
        {
        }

    public:
        static bool deserialize(Path &path, std::istream &is);
        static bool serialize(const Path &path, std::ostream &os);
        static bool load(Path &path, const std::string &file);
        static bool save(const Path &path, const std::string &file);
    };

}

#endif

#ifndef DATA_CONFIGSERIALIZER_HPP_
#define DATA_CONFIGSERIALIZER_HPP_

#include "data/Config.hpp"

namespace tsp
{

    class ConfigSerializer
    {
    private:
        ConfigSerializer() { }
        ~ConfigSerializer() { }
    public:
        static bool deserialize(Config &cfg, std::istream &is);
        static bool serialize(const Config &cfg, std::ostream &os);
        static bool load(Config &cfg, const std::string &file);
        static bool save(const Config &cfg, const std::string &file);
    };

}

#endif

#include <fstream>
#include <json/json.h>
#include "PathSerializer.hpp"

namespace tsp
{
    static bool validatePath(const Json::Value &root)
    {
        if(!root.isArray())
            return false;

        for(const Json::Value & v : root) {
            if(!v.isUInt())
                return false;
        }

        return true;
    }

    bool PathSerializer::deserialize(Path &path, std::istream &is)
    {
        Json::Value root;
        Json::Reader reader;

        if(!reader.parse(is, root, false))
            return false;
        if(!validatePath(root))
            return false;

        path.resize(root.size());
        for(unsigned int i = 0; i < path.size(); ++i)
            path[i] = root[i].asUInt();

        return true;
    }

    bool PathSerializer::serialize(const Path &path, std::ostream &os)
    {
        Json::StyledStreamWriter writer;
        Json::Value root(Json::arrayValue);

        root.resize(path.size());
        for(unsigned int i = 0; i < path.size(); ++i)
            root[i] = path[i];

        writer.write(os, root);

        return true;
    }

    bool PathSerializer::load(Path &path, const std::string &file)
    {
        std::ifstream is(file);
        return deserialize(path, is);
    }

    bool PathSerializer::save(const Path &path, const std::string &file)
    {
        std::ofstream os(file);
        return serialize(path, os);
    }
}

#include <fstream>
#include <json/json.h>
#include "data/StatisticsSerializer.hpp"
#include "utils/StopWatch.hpp"

namespace tsp
{
    static bool validateStatistics(const Json::Value &root)
    {
        bool tmp =  root.isObject() &&
               root["genCount"].isUInt() &&
               root["finalDist"].isDouble() &&
               root["nodeCount"].isUInt() &&
               root["totalTime"].isString() &&
               root["distancePerGen"].isArray() &&
               root["timePerGen"].isArray() &&
               root["distancePerGen"].size() == root["timePerGen"].size();
        if(!tmp)
            return false;

        for(unsigned int i = 0; i < root["distancePerGen"].size(); ++i)
        {
            if(!root["distancePerGen"][i].isDouble())
                return false;
        }

        for(unsigned int i = 0; i < root["timePerGen"].size(); ++i)
        {
            if(!root["timePerGen"][i].isString())
                return false;
        }

        return true;
    }

    bool StatisticsSerializer::deserialize(Statistics &stats, std::istream &is)
    {
        Json::Value root;
        Json::Reader reader;

        if(!reader.parse(is, root, false))
            return false;
        if(!validateStatistics(root))
            return false;

        stats.genCount = root["genCount"].asUInt();
        stats.finalDistance = root["finalDist"].asDouble();
        stats.nodeCount = root["nodeCount"].asUInt();
        stats.totalTime = durationFromStr(root["totalTime"].asString());

        stats.distancePerGen.resize(stats.genCount);
        stats.timePerGen.resize(stats.genCount);

        for(unsigned int i = 0; i < root["distancePerGen"].size(); ++i)
            stats.distancePerGen[i] = root["distancePerGen"].asDouble();

        for(unsigned int i = 0; i < root["timePerGen"].size(); ++i)
            stats.timePerGen[i] =durationFromStr(root["timePerGen"].asString());

        return true;

    }

    bool StatisticsSerializer::serialize(const Statistics &stats, std::ostream &os)
    {
        Json::StyledStreamWriter writer;
        Json::Value root;

        root["genCount"] = stats.genCount;
        root["finalDist"] = stats.finalDistance;
        root["nodeCount"] = stats.nodeCount;
        root["totalTime"] = boost::posix_time::to_simple_string(stats.totalTime);

        root["distancePerGen"] = Json::Value(Json::arrayValue);
        root["timePerGen"] = Json::Value(Json::arrayValue);

        root["distancePerGen"].resize(stats.distancePerGen.size());
        root["timePerGen"].resize(stats.timePerGen.size());

        for(unsigned int i = 0; i < stats.distancePerGen.size(); ++i)
            root["distancePerGen"][i] = stats.distancePerGen[i];

        for(unsigned int i = 0; i < stats.timePerGen.size(); ++i)
            root["timePerGen"][i] = boost::posix_time::to_simple_string(stats.timePerGen[i]);

        writer.write(os, root);

        return true;
    }

    bool StatisticsSerializer::load(Statistics &stats, const std::string &file)
    {
        std::ifstream is(file);
        return deserialize(stats, is);
    }

    bool StatisticsSerializer::save(const Statistics &stats, const std::string &file)
    {
        std::ofstream os(file);
        return serialize(stats, os);
    }

}

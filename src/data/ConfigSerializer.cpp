#include "data/ConfigSerializer.hpp"
#include <fstream>
#include <json/json.h>
#include "utils/StopWatch.hpp"

namespace tsp
{
    static bool validateConfig(const Json::Value &root)
    {
        return root.isObject() &&
               root["graphFile"].isString() &&
               root["pathFile"].isString() &&
               root["populationSize"].isUInt() &&
               root["startNode"].isUInt() &&
               root["elitismRate"].isDouble() &&
               root["fitnessPower"].isUInt() &&
               root["mutationChance"].isDouble() &&
               root["exchangeRate"].isDouble() &&
               (root["generationCount"].isUInt() ||
                       (root["duration"].isString() &&
                               checkDurationStr(root["duration"].asString())));
    }

    bool ConfigSerializer::deserialize(Config &cfg, std::istream &is)
    {
        Json::Value root;
        Json::Reader reader;

        if(!reader.parse(is, root, false))
            return false;
        if(!validateConfig(root))
            return false;

        if(root["generationCount"].isUInt()) {
            cfg.terminateType = TerminateType::GENERATIONS;
            cfg.generationCount = root["generationCount"].asUInt();
        }
        if(root["duration"].isString()) {
            cfg.terminateType = TerminateType::TIME;
            cfg.duration = durationFromStr(root["duration"].asString());
        }

        cfg.graphFile = root["graphFile"].asString();
        cfg.pathFile = root["pathFile"].asString();
        cfg.exchangeRate = root["exchangeRate"].asDouble();
        // solver settings
        cfg.gaSettings.populationSize = root["populationSize"].asUInt();
        cfg.gaSettings.startNode = root["startNode"].asUInt();
        cfg.gaSettings.elitismRate = root["elitismRate"].asDouble();
        cfg.gaSettings.fitnessPow = root["fitnessPower"].asUInt();
        cfg.gaSettings.mutationChance = root["mutationChance"].asDouble();

        return true;
    }

    bool ConfigSerializer::serialize(const Config &cfg, std::ostream &os)
    {
        Json::StyledStreamWriter writer;
        Json::Value root;

        root["generationCount"] = cfg.generationCount;
        root["graphFile"] = cfg.graphFile;
        root["pathFile"] = cfg.pathFile;
        root["populationSize"] = cfg.gaSettings.populationSize;
        root["startNode"] = cfg.gaSettings.startNode;
        root["elitismRate"] = cfg.gaSettings.elitismRate;
        root["fitnessPower"] = cfg.gaSettings.fitnessPow;
        root["mutationChance"] = cfg.gaSettings.mutationChance;
        root["exchangeRate"] = cfg.exchangeRate;

        writer.write(os, root);

        return true;
    }

    bool ConfigSerializer::load(Config &cfg, const std::string &file)
    {
        std::ifstream is(file);
        return deserialize(cfg, is);
    }

    bool ConfigSerializer::save(const Config &cfg, const std::string &file)
    {
        std::ofstream os(file);
        return serialize(cfg, os);
    }
}

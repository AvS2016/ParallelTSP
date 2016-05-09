#include <fstream>
#include <json/json.h>
#include "GraphSerializer.hpp"

namespace tsp
{
    static bool validateGraph(const Json::Value &root)
    {
        return root.isObject() && root["nodes"].isArray();
    }

    bool GraphSerializer::deserialize(Graph &graph, std::istream& is)
    {
        Json::Value root;
        Json::Reader reader;

        if(!reader.parse(is, root, false))
            return false;
        if(!validateGraph(root))
            return false;

        // deserialize nodes
        Json::Value &nodes = root["nodes"];
        graph.resize(nodes.size());
        for(unsigned int i = 0; i < nodes.size(); ++i)
            graph[i] = Node(nodes[i]["id"].asInt(), nodes[i]["x"].asInt(), nodes[i]["y"].asInt());
        return true;
    }

    bool GraphSerializer::serialize(const Graph &graph, std::ostream& os)
    {
        Json::StyledStreamWriter writer;
        Json::Value root;

        root["nodes"] = Json::Value(Json::arrayValue);
        // serialize nodes
        root["nodes"].resize(graph.size());
        Json::Value &nodes = root["nodes"];
        for(unsigned int i = 0; i < nodes.size(); ++i)
        {
            nodes[i]["id"] = graph[i].id();
            nodes[i]["x"] = graph[i].x();
            nodes[i]["y"] = graph[i].y();
        }

        writer.write(os, root);

        return true;
    }

    bool GraphSerializer::load(Graph &graph, const std::string& file)
    {
        std::ifstream is(file);
        return deserialize(graph, is);
    }

    bool GraphSerializer::save(const Graph &graph, const std::string& file)
    {
        std::ofstream os(file);
        return serialize(graph, os);
    }
}



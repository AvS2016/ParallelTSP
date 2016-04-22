#include <fstream>
#include <json/json.h>
#include "GraphSerializer.hpp"

namespace tsp
{
    static bool validateGraph(const Json::Value &root)
    {
        return root.isObject() && root["nodes"].isArray() && root["edges"].isArray();
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
        graph.nodes().resize(nodes.size());
        for(unsigned int i = 0; nodes.size(); ++i)
            graph.nodes()[i] = Node(nodes[i]["id"].asInt(), nodes[i]["x"].asInt(), nodes[i]["y"].asInt());

        // deserialize edges
        Json::Value &edges = root["edges"];
        graph.edges().clear();
        for(unsigned int i = 0; edges.size(); ++i)
        {
            Edge e(edges[i]["start"].asInt(), edges[i]["end"].asInt());
            graph.edges()[e.id()] = e;
        }

        return true;
    }

    bool GraphSerializer::serialize(Graph &graph, std::ostream& os)
    {
        Json::StyledStreamWriter writer;
        Json::Value root;

        root["nodes"] = Json::Value(Json::arrayValue);
        // serialize nodes
        root["nodes"].resize(graph.nodes().size());
        Json::Value &nodes = root["nodes"];
        for(unsigned int i = 0; i < nodes.size(); ++i)
        {
            nodes[i]["id"] = graph.nodes()[i].id();
            nodes[i]["x"] = graph.nodes()[i].x();
            nodes[i]["y"] = graph.nodes()[i].y();
        }

        root["edges"] = Json::Value(Json::arrayValue);
        // serialize edges
        root["edges"].resize(graph.edges().size());
        Json::Value &edges = root["edges"];
        unsigned int i = 0;
        for(std::pair<std::string, Edge> p : graph.edges())
        {
            edges[i]["start"] = p.second.start();
            edges[i]["end"] = p.second.end();
            ++i;
        }

        writer.write(os, root);

        return true;
    }

    bool GraphSerializer::load(Graph &graph, const std::string& file)
    {
        std::ifstream is(file);
        return deserialize(graph, is);
    }

    bool GraphSerializer::save(Graph &graph, const std::string& file)
    {
        std::ofstream os(file);
        return serialize(graph, os);
    }
}



#ifndef DATA_EDGE_HPP_
#define DATA_EDGE_HPP_

#include <string>
#include <sstream>

namespace tsp
{

    class Edge
    {
    private:
        int start_;
        int end_;
        float weight_;
    public:

        Edge()
        : start_(-1), end_(-1), weight_(0)
        { }

        Edge(const int start, const int end, const float weight)
        : start_(start), end_(end), weight_(weight)
        { }

        ~Edge()
        { }

        std::string id() const
        {
            std::stringstream ss;
            ss << start_ << "," << end_;
            return ss.str();
        }

        int start() const
        {
            return start_;
        }

        int end() const
        {
            return end_;
        }

        float weight() const
        {
            return weight_;
        }
    };

}

#endif

#ifndef DATA_NODE_HPP_
#define DATA_NODE_HPP_

namespace tsp
{

    class Node
    {
    private:
        int id_;
        int x_;
        int y_;
    public:
        Node()
        : id_(-1), x_(-1), y_(-1)
        { }

        Node(const int id, const int x, const int y)
        :id_(id), x_(x), y_(y)
        { }

        ~Node()
        { }

        int id() const
        {
            return id_;
        }

        int x() const
        {
            return x_;
        }

        int y() const
        {
            return y_;
        }
    };
}

#endif

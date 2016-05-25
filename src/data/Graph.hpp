#ifndef DATA_GRAPH_HPP_
#define DATA_GRAPH_HPP_

#include <vector>
#include "data/Node.hpp"

namespace tsp
{
    class Graph : public std::vector<Node>{
    	using std::vector<Node>::vector;

    	private:
    		unsigned int width_;
			unsigned int height_;

    	public:
			void setWidth(int x){
				width_ = x;
			}

			void setHeight(int y){
				height_ = y;
			}

			unsigned int width() const{
				return width_;
			}

			unsigned int height() const{
				return height_;
			}
    };
}

#endif

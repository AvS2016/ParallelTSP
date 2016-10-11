#include <iostream>
#include <fstream>
#include <cmath>
#include "GraphConverter.hpp"

namespace tsp
{

    GraphConverter::GraphConverter(const bool drawPath)
        : drawPath_(drawPath), dataFile_(""), plotFile_(""), resultFile_("")
    {
    }

    GraphConverter::~GraphConverter()
    {
    }

    bool GraphConverter::savePlot(const Graph &graph, const Path& path,
            const std::string &fileName)
    {
        dataFile_ = "tsp.dat";
        plotFile_ = "tsp.plt";
        resultFile_ = fileName;

        // write *.dat file
        std::ofstream os(dataFile_);
        os << "# TSP Points\n";

        if (drawPath_) {
            for(unsigned int i = 0; i < path.size(); ++i) {
                unsigned int nodeId = path[i];
                if(nodeId >= graph.size())
                    return false;

                os << graph[nodeId].x() << " " << graph[nodeId].y() << std::endl;
            }
        } else {
            for(unsigned int i = 0; i < graph.size(); ++i) {
                os << graph[i].x() << " " << graph[i].y() << std::endl;
            }
        }
        os.close();

        // write *.plt file
        /*
        set style line <index> {{linetype  | lt} <line_type> | <colorspec>}
                               {{linecolor | lc} <colorspec>}
                               {{linewidth | lw} <line_width>}
                               {{pointtype | pt} <point_type>}
                               {{pointsize | ps} <point_size>}
                               {palette}
        */

        int wHeight = 600, wWidth = 480;
        float density = (float)(wHeight * wWidth) / (graph.size());
        float lineWidth = density / 3000;
        float pointSize = density / 3000;
        std::string plotType = drawPath_ ? "linespoints" : "points";

        os.open(plotFile_, std::ofstream::out);
        os << "set terminal svg size " << wWidth << "," << wHeight <<
           " fname 'Verdana' fsize 10" << std::endl;
        os << "set output '" << resultFile_ << "'" << std::endl;
        os << "set terminal svg enhanced background rgb 'white'" << std::endl;
        os << "set tics font ', 8'" << std::endl;
        os << "unset key" << std::endl;
        os << "set title 'TSP Graph Visualisation (points: " << graph.size() << ")'"
           << std::endl;
        os << "set style line 1 lc rgb '#0060ad' lt 1 lw " << lineWidth << " pt 7 ps "
           << pointSize << "   # --- blue" << std::endl;
        os << "plot '" << dataFile_ << "' with " << plotType << " ls 1" << std::endl;
        os << "quit" << std::endl;
        os.close();

        const std::string cmd = "gnuplot " + plotFile_;
        return system(cmd.c_str()) == 0;

        return 0;
    }
}

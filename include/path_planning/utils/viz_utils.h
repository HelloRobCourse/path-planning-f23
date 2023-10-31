#ifndef PATH_PLANNING_UTILS_VIZ_UTILS_H
#define PATH_PLANNING_UTILS_VIZ_UTILS_H

#include <vector>
#include <string>
#include <fstream>

#include "graph_utils.h"


static inline void generatePlanFile(const Cell& start, const Cell& goal,
                                    const std::vector<Cell>& path, GridGraph& graph,
                                    const std::string& algo = "",
                                    const std::string& out_name = "out.planner")
{
    std::cout << "Saving planning data to file: " << out_name << std::endl;

    std::ofstream outfile;
    outfile.open(out_name);

    outfile << "{ \"path\" : [";

    for (int k = 0; k < path.size(); ++k)
    {
        outfile << "[" + std::to_string(path[k].i) + "," + std::to_string(path[k].j) + "]";
        if (k != path.size() - 1)
            outfile << ",";
    }

    outfile << "], \"visited_cells\":[";
    for (int k = 0; k < graph.visited_cells.size(); ++k)
    {
        outfile << "[" + std::to_string(graph.visited_cells[k].i) + "," + std::to_string(graph.visited_cells[k].j) + "]";
        if (k != graph.visited_cells.size() - 1)
            outfile << ",";
    }
    outfile << "]";

    outfile << ", \"dt\":[";
    for (int k = 0; k < graph.obstacle_distances.size(); ++k)
    {
        outfile << std::to_string(graph.obstacle_distances[k]);
        if (k != graph.obstacle_distances.size() - 1)
            outfile << ",";
    }
    outfile << "]";

    // Now add the entire map file as a string
    outfile << ", \"map\": \"";
    outfile << mapAsString(graph);
    outfile << "\""; // Add closing quote for map file

    // Add start and goal elements to the dict
    outfile << ", \"start\": [" + std::to_string(start.i) + "," + std::to_string(start.j) + "]";
    outfile << ", \"goal\": [" + std::to_string(goal.i) + "," + std::to_string(goal.j) + "]";

    // Save the planning algo used
    outfile << ", \"planning_algo\": \"" + algo + "\"";

    outfile << "}";

    outfile.close();
}

#endif // PATH_PLANNING_UTILS_VIZ_UTILS_H

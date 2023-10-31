#ifndef PATH_PLANNING_GRAPH_SEARCH_GRAPH_SEARCH_H
#define PATH_PLANNING_GRAPH_SEARCH_GRAPH_SEARCH_H

#include <vector>

#include <path_planning/utils/graph_utils.h>


std::vector<Cell> depthFirstSearch(GridGraph& graph, const Cell& start, const Cell& goal);
std::vector<Cell> breadthFirstSearch(GridGraph& graph, const Cell& start, const Cell& goal);
std::vector<Cell> iterativeDeepeningSearch(GridGraph& graph, const Cell& start, const Cell& goal);
std::vector<Cell> aStarSearch(GridGraph& graph, const Cell& start, const Cell& goal);

#endif  // PATH_PLANNING_GRAPH_SEARCH_GRAPH_SEARCH_H

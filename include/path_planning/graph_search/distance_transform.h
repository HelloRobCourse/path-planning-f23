#ifndef PATH_PLANNING_GRAPH_SEARCH_DISTANCE_TRANSFORM_H
#define PATH_PLANNING_GRAPH_SEARCH_DISTANCE_TRANSFORM_H

#include <vector>

#include <path_planning/utils/graph_utils.h>


void distanceTransformSlow(GridGraph& graph);
void distanceTransformManhattan(GridGraph& graph);
std::vector<float> distanceTransformEuclidean1D(std::vector<float>& init_dt);
void distanceTransformEuclidean2D(GridGraph& graph);

#endif  // PATH_PLANNING_GRAPH_SEARCH_DISTANCE_TRANSFORM_H

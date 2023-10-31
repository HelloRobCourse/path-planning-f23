#include <iostream>
#include <vector>
#include <cmath>

#include <path_planning/utils/math_helpers.h>
#include <path_planning/utils/graph_utils.h>

#include <path_planning/graph_search/distance_transform.h>

/**
 * These functions should calculate the distance transform on the given graph
 * and store it in graph.obstacle_distances.
 *
 * This is part of the Distance Transform advanced extensions for Project 3.
 **/


void distanceTransformSlow(GridGraph& graph)
{
    /**
     * TODO (P3 - Practice for Advanced Extension): Perform a distance transform
     * by finding the distance to the nearest occupied cell for each unoccupied
     * cell. Calculate the distance to the nearest cell by looping through all
     * the occupied cells in the graph.
     *
     * Store the result in the vector graph.obstacle_distances.
     **/
}


void distanceTransformManhattan(GridGraph& graph)
{
    /**
     * TODO (P3 - Advanced Extension): Perform a distance transform using the Manhattan distance
     * transform algorithm over a 2D grid.
     *
     * Store the result in the vector graph.obstacle_distances.
     **/
}


std::vector<float> distanceTransformEuclidean1D(std::vector<float>& init_dt)
{
    std::vector<float> dt(init_dt.begin(), init_dt.end());

    /**
     * TODO (P3 - Advanced Extension): Perform a distance transform using the
     * Euclidean distance transform algorithm over a 1D vector using the initial
     * values provided in init_dt.
     *
     * Store the result in the vector dt.
     **/

    return dt;
}


void distanceTransformEuclidean2D(GridGraph& graph)
{
    /**
     * TODO (P3 - Advanced Extension): Perform a distance transform using the
     * Euclidean distance transform algorithm over a 2D grid. Use the
     * distanceTransformEuclidean1D() function.
     *
     * Store the result in the vector graph.obstacle_distances.
     **/
}

#ifndef PATH_PLANNING_GRAPH_SEARCH_GRAPH_UTILS_H
#define PATH_PLANNING_GRAPH_SEARCH_GRAPH_UTILS_H

#include <vector>
#include <string>

#define HIGH 1e6
#define ROBOT_RADIUS 0.137


struct Cell
{
    int i, j;  // Row and column index of the cell in the graph.
};


struct CellNode
{
    CellNode() :
        i(-1),
        j(-1),
        parent(-1),
        distance(HIGH),
        f_score(HIGH),
        visited(false)
    {};

    int i, j;
    int parent;
    bool visited;
    float distance;
    float f_score;
};


struct GridGraph
{
    GridGraph() :
        width(-1),
        height(-1),
        origin_x(0),
        origin_y(0),
        meters_per_cell(0),
        collision_radius(0.15),
        threshold(-100)  // TODO: Adjust threshold.
    {
    };

    int width, height;                      // Width and height of the map in cells.
    float origin_x, origin_y;               // The (x, y) coordinate corresponding to cell (0, 0) in meters.
    float meters_per_cell;                  // Width of a cell in meters.
    float collision_radius;                 // The radius to use to check collisions.
    int8_t threshold;                       // Threshold to check if a cell is occupied or not.

    std::vector<int8_t> cell_odds;          // The odds that a cell is occupied.
    std::vector<float> obstacle_distances;  // The distance from each cell to the nearest obstacle.

    std::vector<Cell> visited_cells;        // A list of visited cells. Used for visualization.

    std::vector<CellNode> nodes;            // The nodes corresponding to each cell.
};


/**
 * Checks whether the graph is loaded.
 */
bool isLoaded(const GridGraph& graph);

/**
 * Loads graph data from a file.
 * @param  file_path  The map file to read.
 * @param  graph      The graph to populate with data from the file.
 */
bool loadFromFile(const std::string& file_path, GridGraph& graph);

/**
 * Converts all map data to a string. This is helpful for saving to a file.
 * @param  graph  The graph to convert to a string.
 */
std::string mapAsString(GridGraph& graph);

/**
 * Initializes the graph data.
 * @param  graph  The graph to initialize.
 */
void initGraph(GridGraph& graph);

/**
 * Converts a cell coordinate to the corresponding index in the graph.
 * @param  i      The row index of the cell in the graph.
 * @param  j      The column index of the cell in the graph.
 * @param  graph  The graph the cell belongs to.
 * @return  The index of the cell in the graph data.
 */
int cellToIdx(int i, int j, const GridGraph& graph);

/**
 * Converts an index in the graph to the corresponding cell.
 * @param  idx    The index of the cell in the graph data.
 * @param  graph  The graph the cell belongs to.
 * @return  The cell coordinate corresponding to the given index.
 */
Cell idxToCell(int idx, const GridGraph& graph);

/**
 * Converts a global position to the corresponding cell in the graph.
 * @param  x      The global x position in meters.
 * @param  y      The global y position in meters.
 * @param  graph  The graph the cell belongs to.
 * @return  The cell coordinate in the graph.
 */
Cell posToCell(float x, float y, const GridGraph& graph);

/**
 * Converts a cell coordinate in the graph to the corresponding global position.
 * @param  i      The row index of the cell in the graph.
 * @param  j      The column index of the cell in the graph.
 * @param  graph  The graph the cell belongs to.
 * @return  A vector of length 2 containing the global position, [x, y].
 */
std::vector<float> cellToPos(int i, int j, const GridGraph& graph);

/**
 * Checks whether the provided cell is within the bounds of the graph.
 * @param  i      The row index of the cell in the graph.
 * @param  j      The column index of the cell in the graph.
 * @param  graph  The graph the cell belongs to.
 */
bool isCellInBounds(int i, int j, const GridGraph& graph);

/**
 * Checks whether the provided index in the graph is occupied.
 * @param  idx    The index of the cell in the graph data.
 * @param  graph  The graph the cell belongs to.
 */
bool isIdxOccupied(int idx, const GridGraph& graph);

/**
 * Checks whether the provided cell in the graph is occupied.
 * @param  i      The row index of the cell in the graph.
 * @param  j      The column index of the cell in the graph.
 * @param  graph  The graph the cell belongs to.
 */
bool isCellOccupied(int i, int j, const GridGraph& graph);

/**
 * Finds the neighbors of the cell at the given index.
 * @param  idx    The index of the cell in the graph data.
 * @param  graph  The graph the cell belongs to.
 * @return  A vector containing the indices of each of the valid neighbors.
 */
std::vector<int> findNeighbors(int idx, const GridGraph& graph);

/**
 * Checks whether the provided index in the graph is within the defined
 * collision radius of an obstacle using the distance transform.
 *
 * Warning: Distance transform values must be stored in graph.obstacle_distances
 * for this function to work.
 * @param  idx    The index of the cell in the graph data.
 * @param  graph  The graph the cell belongs to.
 */
bool checkCollisionFast(int idx, const GridGraph& graph);

/**
 * Checks whether the provided index in the graph is within the defined
 * collision radius of an obstacle by checking all the cells in a radius of the
 * given index.
 * @param  idx    The index of the cell in the graph data.
 * @param  graph  The graph the cell belongs to.
 */
bool checkCollision(int idx, const GridGraph& graph);

/**
 * Returns the parent of the node at the given index in the graph.
 * @param  idx    The index of the node in the graph data.
 * @param  graph  The graph the node belongs to.
 */
int getParent(int idx, const GridGraph& graph);

/**
 * Returns the score of the node at the given index in the graph.
 * @param  idx    The index of the node in the graph data.
 * @param  graph  The graph the node belongs to.
 */
float getScore(int idx, const GridGraph& graph);

/**
 * Find the lowest score cell in the given list.
 * @param  node_list  List of node indices.
 * @param  graph      The graph the node belongs to.
 * @return  The index of the lowest score node in the list.
 */
int findLowestScore(const std::vector<int>& node_list, const GridGraph& graph);

/**
 * Traces a path from the given goal back to the start position.
 * @param  goal   The index of the goal node in the graph data.
 * @param  graph  The graph the node belongs to.
 * @return  A vector containing each cell, from the start to the goal.
 */
std::vector<Cell> tracePath(int goal, const GridGraph& graph);

static std::vector<std::array<float, 3> > cellsToPoses(std::vector<Cell>& path, GridGraph& graph)
{
    std::vector<std::array<float, 3> > pose_path;

    for (Cell& cell : path)
    {
        std::array<float, 3> pose;
        auto position = cellToPos(cell.i, cell.j, graph);
        pose[0] = position[0];
        pose[1] = position[1];
        pose[2] = 0;
        pose_path.push_back(pose);
    }

    return pose_path;
};

#endif  // PATH_PLANNING_GRAPH_SEARCH_GRAPH_UTILS_H

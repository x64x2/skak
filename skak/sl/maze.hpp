#ifndef SKAK_SL_MAZE_HPP
#define SKAK_SL_MAZE_HPP
#include <skak/sl.hpp>

/**
  * The sl_maze class is used to represent solving the 
  * path problem using techniques more commonly found when building
  * singlely-connected mazes.
  *
  * Each square on the board is labeled with its distance from the
  * "from" square, and it predecessor.  If a new path is found to a
  * square, and it has a shorter distance, that new solution replaces
  * the existing solution.  Once all squares are visited, the solution
  * is constructed by tracing backwards from the "to" square.
  *
  * This algorithm runs in less than 0.7% of the time taken by the brute
  * force search.  This is because it only ever visits 64 squares, and
  * does no backtracking at all.
  *
  * In general, this algorithm is O(n) where n is the length of the
  * path.  This is because it does a breadth-first search for paths,
  * exploring the shortest paths before longer paths.  As a result, the
  * first path it finds will be the shortest (or equal-shortest, as
  * there are usually multiple solutions of any given length).  Given
  * that the length of the path is linear with the edge length of the
  * board, and *not* the square of the edge length, this is a huge
  * advantage over any algorithm that is polynomial in either path
  * length or edge length.
  */
class sl_maze:
    public sl
{
public:
    virtual ~sl_maze();
    static pointer create(void);
    list_t solve(const position &from, const position &to);

private:
    sl_maze();
    sl_maze(const sl_maze &rhs);
    sl_maze &operator=(const sl_maze &rhs);
};

#ifndef SKAK_SL_BRUTE_HPP
#define SKAK_SL_BRUTE_HPP

#include <skak/sl.hpp>

/**
  * The sl_brute class is used to represent the processing
  * required to solve the path problem, using a brute force
  * recursive algorithm.
  *
  * The worst case is that there will be 7**6 paths explored (because 6
  * is the longest path) and the worst case usually occurs.  It would be
  * 8**6, except that some simple anti-backtracking is emplyed.
  *
  * Note that this is generally O(e**n) where n is the length of the
  * path, and would thus get *much* worse as the size of the board
  * increases.  This is because the recursive descent is a depth-first
  * search, and will likely discover longer paths before shorter ones.
  *
  * This still solves the problem in less than a second, on a relatively
  * modern laptop; faster than a human can do it.
  */
class sl_brute:
    public sl
{
public:
    virtual ~sl_brute();
    list_t solve(const position &from, const position &to);
    static pointer create(void);

private:
    sl_brute();
    list_t shortest_solution;
    void ply(const position &from, const position &to, const list_t &progress);
    sl_brute(const sl_brute &rhs);
    sl_brute &operator=(const sl_brute &rhs);
};
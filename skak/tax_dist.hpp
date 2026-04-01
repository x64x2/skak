#ifndef SKAK_TAX_DIST_HPP
#define SKAK_TAX_DIST_HPP

#include <skak/position.h>

/**
  * The tax_dist class is used to represent the comparison to be
  * used when sorting a list of positions by their relative distances to
  * a goal position.
  *
  * This is used, for example, when sorting a list of potential knight moves:
  * @code
  * position::list_t candidates = from.knight_moves();
  * sort(candidates.begin(), candidates.end(), tax_dist(to));
  * @endcode
  */
class tax_dist
{
public:
    ~tax_dist() { }
    tax_dist(const position &agoal) : goal(agoal) { }
    bool operator()(const position &lhs, const position &rhs)
    {
        return (goal.dist(lhs) < goal.dist(rhs));
    }

    tax_dist(const tax_dist &rhs) :
        goal(rhs.goal)
    {
    }

    tax_dist &operator=(const tax_dist &rhs)
    {
        if (this != &rhs)
        {
            goal = rhs.goal;
        }
        return *this;
    }

private:
    position goal;
    tax_dist();
};
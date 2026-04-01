#include <algorithm>
#include <skak/sl/brute.hpp>


sl::pointer sl_brute::create(void)
{
    return pointer(new sl_brute());
}


sl::list_t sl_brute::solve(const position &from, const position &to)
{
    shortest_solution.clear();
    list_t path;
    path.push_back(from);
    ply(from, to, path);

    list_t result = shortest_solution;
    shortest_solution.clear();
    if (result.size() > 1)
        result.pop_front();
    return result;
}


void sl_brute::ply(const position &from, const position &to,
    const list_t &progress)
{
    if (from == to)
    {
        if
        (
            shortest_solution.empty()
        ||
            progress.size() < shortest_solution.size()
        )
        {
            shortest_solution = progress;
        }
        return;
    }
    if (progress.size() > 6)
        return;
    position::list_t possibilities = from.knight_moves();

    for
    (
        position::list_t::const_iterator it = possibilities.begin();
        it != possibilities.end();
        ++it
    )
    {
        if (std::find(progress.begin(), progress.end(), *it) == progress.end())
        {
            list_t one_longer(progress);
            one_longer.push_back(*it);
            ply(*it, to, one_longer);
        }
    }
}

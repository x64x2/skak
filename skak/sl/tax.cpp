#include <skak/sl/tax.hpp>
#include <skak/tax_dist.hpp>

sl_taxi::pointer sl_taxi::create(void)
{
    return pointer(new sl_taxi());
}

sl::list_t sl_taxi::solve(const position &from, const position &to)
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

void sl_taxi::ply(const position &from, const position &to,const list_t &progress)
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
    size_t too_big = shortest_solution.empty() ? 7 : shortest_solution.size();
    if (progress.size() >= too_big)
        return;

    position::list_t possibilities = from.knight_moves();
    sort(possibilities.begin(), possibilities.end(), tax_dist(to));

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

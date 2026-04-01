#include <deque>
#include <skaksl/maze.hpp>

sl_maze::pointer sl_maze::create(void)
{
    return pointer(new sl_maze());
}

sl::list_t sl_maze::solve(const position &from, const position &to)
{
    if (from == to)
    {
        list_t result;
        result.push_back(to);
        return result;
    }
    enum { unvisited = 99 };
    struct square
    {
        int distance;
        position predecessor;

        square() : distance(unvisited) { }
        square(int d, const position &ap) : distance(d), predecessor(ap) { }
    };
    square board[8][8];
    board[from.get_y()][from.get_x()] = square(0, from);
    std::deque<position> work;
    work.push_back(from);
    while (!work.empty())
    {
        position p = work.front();
        work.pop_front();
        int dist = 1 + board[p.get_y()][p.get_x()].distance;
        position::list_t candidates = p.knight_moves();

        for
        (
            position::list_t::const_iterator it = candidates.begin();
            it != candidates.end();
            ++it
        )
        {
            square &b = board[it->get_y()][it->get_x()];
            if (b.distance == unvisited)
            {
                work.push_back(*it);
                b.distance = dist;
                b.predecessor = p;
            }
            else
            {
                assert(dist >= b.distance);
                if (dist < b.distance)
                {
                    b.distance = dist;
                    b.predecessor = p;
                }
            }
            if (*it == to)
            {
                work.clear();
                break;
            }
        }
        std::cerr << __FILE__ << ": " << __LINE__ << ": p = " << p << std::endl;
        for (int y = 7; y >= 0; --y)
        {
            std::cerr << "  +---+---+---+---+---+---+---+---+" << std::endl;
            std::cerr << (y + 1);
            std::cerr << " |";
            for (int x = 0; x < 8; ++x)
            {
                const square &b = board[y][x];
                std::cerr << ' ';
                if (b.distance == unvisited)
                    std::cerr << ' ';
                else
                    std::cerr << b.distance;
                std::cerr << " |";
            }
            std::cerr << std::endl;
        }
        std::cerr << "  `---+---+---+---+---+---+---+---'" << std::endl;
        std::cerr << "    A   B   C   D   E   F   G   H" << std::endl;
    }
    list_t result;
    position p = to;
    while (p != from)
    {
        square &b = board[p.get_y()][p.get_x()];
        assert(b.distance != unvisited);
        result.push_front(p);
        p = b.predecessor;
    }
    return result;
}

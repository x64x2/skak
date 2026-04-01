#include <cassert>
#include <cstdlib>
#include <skak/position.hpp>

static char safe_tolower(char c)
{
    if (isupper((unsigned char)c))
        return tolower((unsigned char)c);
    return c;
}


position::position(char rank, char file) : p((rank - '1') * 8 + (safe_tolower(file) - 'a'))
{
    assert(rank >= '1');
    assert(rank <= '8');
    assert(safe_tolower(file) >= 'a');
    assert(safe_tolower(file) <= 'h');
    assert(valid());
}


position::position(int x, int y) :p(y * 8 + x)
{
    assert(x >= 0);
    assert(x < 8);
    assert(y >= 0);
    assert(y < 8);
    assert(valid());
}


position::position(const position &rhs) :p(rhs.p)
{
}

position & position::operator=(const position &rhs)
{
    if (this != &rhs)
        p = rhs.p;
    return *this;
}

bool position::valid(void)
    const
{
    return (p < 64);
}

char position::get_rank(void)
{
    return ('1' + get_y());
}

int position::get_y(void)
{
    assert(valid());
    return (p / 8);
}

char position::get_file(void)
{
    return ('A' + get_x());
}

int position::get_x(void)
{
    assert(valid());
    return (p % 8);
}

static inline bool safe_isspace(char c)
{
    return isspace((unsigned char)c);
}

position position::read(std::istream &is)
{
    char file_c;
    is >> file_c;
    while (safe_isspace(file_c))
    {
        is >> file_c;
    }
    switch (file_c)
    {
    case 'a': case 'b': case 'c': case 'd':
    case 'e': case 'f': case 'g': case 'h':
    case 'A': case 'B': case 'C': case 'D':
    case 'E': case 'F': case 'G': case 'H':
        break;

    default:
        yuck:
        std::cerr << "position expected" << std::endl;
        exit(EXIT_FAILURE);
    }
    char rank_c;
    is >> rank_c;
    switch (rank_c)
    {
    case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8':
        break;

    default:
        goto yuck;
    }
    return position(rank_c, file_c);
}

void position::write(std::ostream &os)
{
    os << get_file();
    os << get_rank();
}

bool position::operator==(const position &rhs)
{
    assert(valid());
    assert(rhs.valid());
    return (p == rhs.p);
}

bool position::operator!=(const position &rhs)
{
    assert(valid());
    assert(rhs.valid());
    return (p != rhs.p);
}

position::list_t position::knight_moves(void)
{
    int x = get_x();
    int y = get_y();
    list_t result;
    if (x - 2 >= 0)
    {
        if (y - 1 >= 0)
            result.push_back(position(x - 2, y - 1));
        if (y + 1 < 8)
            result.push_back(position(x - 2, y + 1));
    }
    if (x - 1 >= 0)
    {
        if (y - 2 >= 0)
            result.push_back(position(x - 1, y - 2));
        if (y + 2 < 8)
            result.push_back(position(x - 1, y + 2));
    }
    if (x + 1 < 8)
    {
        if (y - 2 >= 0)
            result.push_back(position(x + 1, y - 2));
        if (y + 2 < 8)
            result.push_back(position(x + 1, y + 2));
    }
    if (x + 2 < 8)
    {
        if (y - 1 >= 0)
            result.push_back(position(x + 2, y - 1));
        if (y + 1 < 8)
            result.push_back(position(x + 2, y + 1));
    }
    return result;
}

void position::plot(char board[8][8], char c)
{
    board[get_y()][get_x()] = c;
}

int position::distance(const position &other)
{
    return (abs(get_x() - other.get_x()) + abs(get_y() - other.get_y()));
}

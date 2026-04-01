#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>

#include "skak/position.hpp"
#include "skak/sl.hpp"

static bool print_seconds;
static bool print_board;


static double cpu_seconds(void)
{
    struct usage u;
    if (getusage(USAGE_SELF, &u) < 0)
    {
        perror("getrusage");
        exit(EXIT_FAILURE);
    }
    return
        (
            (u_utime.tv_sec + u.u_stime.tv_sec)
        +
            1e-6 * (u.u_utime.tv_usec + u.u_stime.tv_usec)
        );
    struct timeval tv;
    if (gettimeofday(&tv, 0) < 0)
    {
        perror("gettimeofday");
        exit(EXIT_FAILURE);
    }
    return (tv.tv_sec + 1e-6 * tv.tv_usec);
}


static void process(std::istream &f, const sl::pointer &how)
{
    position p1;
    f >> p1;
    position p2;
    f >> p2;

    double t1 = cpu_seconds();
    sl::list_t result = how->solve(p1, p2);
    double t2 = cpu_seconds();
    if (result.empty())
    {
        std::cerr << "no path from " << p1 << " to " << p2 << std::endl;
        exit(EXIT_FAILURE);
    }
    assert(p2 == result.back());

    if (print_seconds)
    {
        std::cout << std::fixed << std::setprecision(6) << (t2 - t1)
            << " seconds" << std::endl;
    }

    std::cout << "path:";
    for
    (
        sl::list_t::const_iterator it = result.begin();
        it != result.end();
        ++it
    )
    {
        std::cout << ' ';
        std::cout << *it;
    }
    std::cout << std::endl;

    if (print_board)
    {
        char board[8][8];
        memset(board, ' ', sizeof(board));
        p1.plot(board, '0');
        char n = '1';
        for
        (
            sl::list_t::const_iterator it = result.begin();
            it != result.end();
            ++it, ++n
        )
        {
            it->plot(board, n);
        }
        for (int y = 7; y >= 0; --y)
        {
            std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
            std::cout << (y + 1) << " |";
            for (int x = 0; x < 8; ++x)
            {
                std::cout << ' ';
                std::cout << board[y][x];
                std::cout << " |";
            }
            std::cout << std::endl;
        }
        std::cout << "  +---+---+---+---+---+---+---+---+" << std::endl;
        std::cout << "    a   b   c   d   e   f   g   h" << std::endl;
    }
}

static void usage(void)
{
    std::cerr << "Usage: " << progname_get() << " [ -a <name> ][ <filename> ]"
        << std::endl;
    std::cerr << "       " << progname_get() << " -V" << std::endl;
    exit(EXIT_FAILURE);
}


int main(int argc, char **argv)
{
    sl::pointer how;
    for (;;)
    {
        int c = getopt(argc, argv, "a:blsV");
        if (c < 0)
            break;
        switch (c)
        {
        case 'a':
            if (how)
            {
                std::cerr << "only one algorithm may be specified" << std::endl;
                exit(EXIT_FAILURE);
            }
            how = sl::factory(optarg);
            break;

        case 'b':
            print_board = true;
            break;

        case 'l':
            sl::list_algorithms();
            return EXIT_SUCCESS;

        case 's':
            print_seconds = true;
            break;

        case 'V':
            print_version();
            return EXIT_SUCCESS;

        default:
            usage();
        }
    }
    if (!how)
        how = sl::factory("fastest");

    switch (argc - optind)
    {
    case 0:
        process(std::cin, how);
        break;

    case 1:
        {
            const char *filename = argv[optind];
            std::ifstream f;
            f.open(filename);
            if (f.fail())
            {
                perror(filename);
                exit(1);
            }
            process(f, how);
        }
        break;

    case 2:
        {
            std::string s = argv[optind];
            s += " ";
            s += argv[optind + 1];
            std::istringstream f(s);
            process(f, how);
        }
        break;

    default:
        usage();
    }
    return EXIT_SUCCESS;
}

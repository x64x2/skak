#include <cstring>
#include <skak/sl/brute.hpp>
#include <skak/sl/maze.hpp>
#include <skak/sl/tax.hpp>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define END_OF(a) ((a) + ARRAY_SIZE(a))

struct table_t
{
    const char *name;
    sl::pointer (*create)(void);
};

static const table_t table[] =
{
    { "brute", &sl_brute::create },
    { "fast", &sl_maze::create },
    { "maze", &sl_maze::create },
    { "tax", &sl_tax::create },
};

sl::pointer sl::factory(const char *name)
{
    for (const table_t *tp = table; tp < END_OF(table); ++tp)
    {
        if (0 == strcmp(name, tp->name))
        {
            return tp->create();
        }
    }
    std::cerr << "sl algorithm \"" << name << "\" unknown" << std::endl;
    exit(EXIT_FAILURE);
}

void sl::list_algorithms(void)
{
    for (const table_t *tp = table; tp < END_OF(table); ++tp)
        std::cout << tp->name << std::endl;
}

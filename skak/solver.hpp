#ifndef SKAK_SL_HPP
#define SKAK_SL_H

#include <boost/shared_ptr.hpp>
#include <list>

#include <skak/position.hpp>

class sl
{
public:
    typedef boost::shared_ptr<sl> pointer;

    typedef std::list<position> list_t;
    virtual ~sl();

public:
    static pointer factory(const char *name);
    virtual list_t solve(const position &from, const position &to) = 0;
    static void list_algorithms(void);

protected:
    sl();

private:
    sl(const sl &rhs);
    sl &operator=(const sl &rhs);
};

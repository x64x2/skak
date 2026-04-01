#ifndef skak_SL_TAX_HPP
#define skak_SL_TAX_HPP

#include <skak/sl.h>

class sl_taxi:
    public sl
{
public:
    virtual ~sl_taxi();
    static pointer create(void);
    list_t solve(const position &from, const position &to);

private:
    sl_taxi();
    list_t shortest_solution;
    void ply(const position &from, const position &to, const list_t &progress);
    sl_taxi(const sl_taxi &rhs);
    sl_taxi &operator=(const sl_taxi &rhs);
};
#ifndef SKAK_POSITION_HPP
#define SKAK_POSITION_HPP

#include <iostream>
#include <vector>

/**
  * The position class is used to represent a position on a chess board.
  * The board is assumed to be a standard 8x8 board.
  *
  * Input and output using algebraic notation is available.  See
  * http://en.wikipedia.org/wiki/Algebraic_notation_%28chess%29
  * for more information.
  *
  * Rows (called "ranks") are numbered 1..8, when viewed from white's
  * side of the board, with 1 closest (at the bottom) and 8 farthest (at
  * the top).
  *
  * Columns (called "files") are numbered 'a' to 'h', when viewed from
  * white's side of the board with 'a' on the left and 'h' on the right.
  */
class position
{
public:
    typedef std::vector<position> list_t;

    ~position();
    position();
    position(char rank, char file);
    position(const position &rhs);
    position &operator=(const position &rhs);
    list_t knight_moves(void) const;
    static position read(std::istream &is);
    void write(std::ostream &os) const;
    bool operator==(const position &rhs) const;
    bool operator!=(const position &rhs) const;
    void plot(char board[8][8], char c) const;

    /**
      * The distance method may be used to calculate the taxi-cab
      * distance (see http://en.wikipedia.org/wiki/Taxicab_geometry)
      * between this point and the given point.
      *
      * @param elsewhere
      *     The other position of interest.
      */
    int distance(const position &elsewhere) const;

private:
    position(int x, int y);
    unsigned p;
    bool valid(void) const;
    char get_rank(void) const;
    char get_file(void) const;

public:
    int get_x(void) const;
    int get_y(void) const;
};

static inline std::istream & operator>>(std::istream &is, position &p)
{
    p = position::read(is);
    return is;
}

static inline std::ostream & operator<<(std::ostream &os, const position &p)
{
    p.write(os);
    return os;
}
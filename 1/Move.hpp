#ifndef _MOVE_HPP
#define _MOVE_HPP

#include <list>
#include "piece.hpp"

class Move{
  public:
    Move(int cr, int cc, int nr, int nc);
    int cur_row;
    int cur_col;
    int next_row;
    int next_col;
};

#endif

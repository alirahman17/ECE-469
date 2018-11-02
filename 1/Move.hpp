#ifndef _MOVE_HPP
#define _MOVE_HPP

#include <list>
#include <vector>
#include "piece.hpp"

using namespace std;

class Move{
  public:
    Move(int cr, int cc, int nr, int nc, vector<int> mr, vector<int> mc);
    int cur_row;
    int cur_col;
    int next_row;
    int next_col;
    vector<int> mrow;
    vector<int> mcol;
};

#endif

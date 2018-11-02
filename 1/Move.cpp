#include "Move.hpp"

Move::Move(int cr, int cc, int nr, int nc, vector<int> mr, vector<int> mc){
  cur_row = cr;
  cur_col = cc;
  next_row = nr;
  next_col = nc;
  mrow = mr;
  mcol = mc;
}

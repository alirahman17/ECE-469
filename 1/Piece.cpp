#include "piece.hpp"

using namespace std;

Piece::Piece(int r, int c, int p, int t){
  this->row = r;
  this->col = c;
  this->player = p;
  this->type = t;
}

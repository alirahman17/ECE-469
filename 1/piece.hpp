#ifndef _PIECE_HPP
#define _PIECE_HPP

class Piece {
  public:
    Piece(int r, int c, int p, int t = 1);
    int row;
    int col;
    int player; //1 is P1, 2 is P2
    int type;   //1 is Normal, 2 is King
};

#endif

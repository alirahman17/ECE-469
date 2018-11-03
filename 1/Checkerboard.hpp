#ifndef _CHECKERBOARD_HPP
#define _CHECKERBOARD_HPP

#include <list>
#include "piece.hpp"
#include "Move.hpp"

using namespace std;

class CheckerBoard {
  public:
    CheckerBoard(int load[8][8]);
    int board[8][8];
    list<Move *> m1;
    list<Move *> m2;
    list<Piece *> p1;
    list<Piece *> p2;
    list <Move *> get_moves(list<Piece *> p1, list <Move *> m1, int p, vector<int> jr, vector<int> jc, Piece* pj);
    vector<vector<int>> check_jumps(Piece* pj, vector<int> jr, vector<int> jc);
    Piece * findPiece(int r, int c, list<Piece *> p);
    int print_moves(int p);
    void make_move(int m);
    void updateBoard();
    void printBoard();

  private:
    void printBlack();
    void printWhite();
    void printP1();
    void printP2();
    void printP1k();
    void printP2k();

};

#endif

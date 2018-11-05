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
    list<Move *> get_moves(list<Piece *> p1, int p, vector<int> jr, vector<int> jc);
    vector<vector<int>> check_jumps(Piece* pj, vector<int> jr, vector<int> jc, int tboard[8][8]);
    vector<int> aimove;
    Piece * findPiece(int r, int c, list<Piece *> p);
    int print_moves(int p);
    int make_move(int m);
    void updateBoard();
    void printBoard();
    int AlphaBeta(int depth, int Alpha, int Beta, list <Move *> mi, list<Piece *> pi, int p, double timeRemaining, double startTime, double stoptime, int odepth);
    int evaluate_move(list<Move *> mi, list<Piece *> pi);
    int evaluate_move2(list<Move *> mi, list<Piece *> pi);
    int ai_move(double timeRemaining, int p);
    list <Piece *> sample_move(int m, list <Move *> mn, list <Piece *> pn);
    int heuristicBoard[8][8] = {
      {0,4,0,4,0,4,0,4},
      {4,0,3,0,3,0,3,0},
      {0,3,0,2,0,2,0,4},
      {4,0,2,0,1,0,3,0},
      {0,3,0,1,0,2,0,4},
      {4,0,2,0,1,0,3,0},
      {0,3,0,2,0,2,0,4},
      {4,0,4,0,4,0,4,0}
    };

  private:
    void printBlack();
    void printWhite();
    void printP1();
    void printP2();
    void printP1k();
    void printP2k();

};

#endif

#include <iostream>
#include <string>
#include "Checkerboard.hpp"
#include "piece.hpp"
#include <stdlib.h>     /* srand, rand */
#include <time.h>

using namespace std;

int board[8][8] = {
  {0,1,0,1,0,1,0,1},
  {1,0,1,0,1,0,1,0},
  {0,1,0,1,0,1,0,1},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {2,0,2,0,2,0,2,0},
  {0,2,0,2,0,2,0,2},
  {2,0,2,0,2,0,2,0}
};

string option;
int opt = 0;

int main(){
  bool game = 1;
  CheckerBoard *testBoard = new CheckerBoard(board);
  testBoard->printBoard();
  int k = 0;
  while(game){
    //Player 1
    cout << "Select an Option\n";
    k = testBoard->print_moves(1);
    if(k == 0)
      break;
    //getline (cin,option);
    srand (time(NULL));
    int opt = rand() % k;
    cout << "You Chose: " << opt + 1 << endl;
    testBoard->make_move(opt + 1);
    testBoard->printBoard();
    //Player 2
    cout << "Select an Option\n";
    k = testBoard->print_moves(2);
    if(k == 0)
      break;
    //getline (cin,option);
    //int opt2 = stoi(option,nullptr,0);
    srand (time(NULL));
    int opt2 = rand() % k;
    cout << "You Chose: " << opt2 + 1 << endl;
    testBoard->make_move(opt2 + 1);
    testBoard->printBoard();
  }

  return 0;
}

#include <iostream>
#include <string>
#include "Checkerboard.hpp"
#include "piece.hpp"

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


  while(game){
    //Player 1
    cout << "Select an Option\n";
    testBoard->print_moves(1);
    getline (cin,option);
    int opt = stoi(option,nullptr,0);
    cout << "You Chose: " << opt << endl;
    testBoard->make_move(opt);
    testBoard->printBoard();
    //Player 2
    cout << "Select an Option\n";
    testBoard->print_moves(2);
    getline (cin,option);
    int opt2 = stoi(option,nullptr,0);
    cout << "You Chose: " << opt2 << endl;
    testBoard->make_move(opt2);
    testBoard->printBoard();
  }

  return 0;
}

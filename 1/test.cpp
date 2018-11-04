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

/*int board[8][8] = {
  {0,3,0,0,0,0,0,0},
  {0,0,2,0,4,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0}
};*/

string option,num,tm;
int comptime;
int comp = 0;
int z = -1;
int game = 1;
bool play = true;

int main(){
  cout << "How Many Computers Are Playing (Options are 0,1,2; Default = 1)\n";
  getline (cin,num);
  comp = stoi(num,nullptr,0);
  //cout << "COMP = " << comp << endl;
  if(comp == 0){
    game = 0;
  } else if(comp == 2){
    cout << "What is the time limit for the Computer to make a move in seconds (Default 5s)\n";
    getline (cin,tm);
    comptime = stoi(num,nullptr,0);
    cout << "Time = " << comptime << " seconds\n";
    game = 2;
  } else{
    cout << "What is the time limit for the Computer to make a move in seconds (Default 5s)\n";
    getline (cin,tm);
    comptime = stoi(tm,nullptr,0);
    cout << "Time = " << comptime << " seconds\n";
    game = 1;
  }
  CheckerBoard *testBoard = new CheckerBoard(board);
  testBoard->printBoard();
  int k = 0;
  if(game == 0){
    while(play){
      //Player 1
      z = -1;
      while(z != 0){
        cout << "Select an Option\n";
        k = testBoard->print_moves(1);
        if(k == 0)
          return 2;
        getline (cin,option);
        int opt = stoi(option,nullptr,0);
        cout << "You Chose: " << opt << endl;
        z = testBoard->make_move(opt);
        testBoard->printBoard();
      }
      z = -1;
      //Player 2
      while(z != 0){
        cout << "Select an Option\n";
        k = testBoard->print_moves(2);
        if(k == 0)
          return 1;
        getline (cin,option);
        int opt2 = stoi(option,nullptr,0);
        cout << "You Chose: " << opt2 << endl;
        z = testBoard->make_move(opt2);
        testBoard->printBoard();
      }
    }
  } else if(game == 1){
    while(play){
      //Player 1
      z = -1;
      while(z != 0){
        cout << "Select an Option\n";
        k = testBoard->print_moves(1);
        if(k == 0)
          return 2;
        getline (cin,option);
        int opt = stoi(option,nullptr,0);
        cout << "You Chose: " << opt << endl;
        z = testBoard->make_move(opt);
        testBoard->printBoard();
      }
      z = -1;
      //Player 2
      while(z != 0){
        cout << "Select an Option\n";
        k = testBoard->print_moves(2);
        if(k == 0)
          return 1;
        //srand (time(NULL));
        //int opt2 = rand() % k;
        int opt2 = testBoard->ai_move((double)comptime);
        cout << "Computer Chose: " << opt2 << endl;
        z = testBoard->make_move(opt2);
        testBoard->printBoard();
      }
    }
  } else {
    while(play){
      //Player 1
      z = -1;
      while(z != 0){
        cout << "Select an Option\n";
        k = testBoard->print_moves(1);
        if(k == 0)
          return 2;
        int opt = testBoard->ai_move((double)comptime);
        cout << "Computer 1 Chose: " << opt << endl;
        z = testBoard->make_move(opt);
        testBoard->printBoard();
      }
      z = -1;
      //Player 2
      while(z != 0){
        cout << "Select an Option\n";
        k = testBoard->print_moves(2);
        if(k == 0)
          return 1;
        int opt2 = testBoard->ai_move((double)comptime);
        cout << "Computer Chose: " << opt2 << endl;
        z = testBoard->make_move(opt2);
        testBoard->printBoard();
      }
    }
  }







  return 0;
}

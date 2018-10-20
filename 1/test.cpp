#include <iostream>
#include "Checkerboard.h"

using namespace std;

char test = 219;

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

void printBlack(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219 << 219 << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}
void printWhite(){
  cout << "\33[3" << 7 << ";4" << 7 << "m";
  cout << 219 << 219 << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void printP1(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 1 << ";4" << 1 << "m";
  cout << 219;
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void printP2(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 7 << ";4" << 7 << "m";
  cout << 219;
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void printBoard(){
  for(int i = 0; i < 8; i++){
    if(i % 2 == 1){
      for (int k = 0; k < 5; k++){
        for(int j = 0; j < 8; j++){
          if(k == 2){
            if(board[i][j] == 1){
              printP1();
            }
            else if(board[i][j] == 2){
              printP2();
            }
            else if(j % 2 == 1){
              printWhite();
            }
            else {
              printBlack();
            }
          } else{
            if(j % 2 == 1){
              printWhite();
            }
            else {
              printBlack();
            }
          }
        }
        cout << endl;
      }
    } else{
      for (int k = 0; k < 5; k++){
        for(int j = 0; j < 8; j++){
          if(k == 2){
            if(board[i][j] == 1){
              printP1();
            }
            else if(board[i][j] == 2){
              printP2();
            }
            else if(j % 2 == 1){
              printBlack();
            }
            else {
              printWhite();
            }
          } else{
            if(j % 2 == 1){
              printBlack();
            }
            else {
              printWhite();
            }
          }
        }
        cout << endl;
      }
    }
  }
}


int main(){

  printBoard();



  //CheckerBoard checkerBoard;
  //checkerBoard.initBoard();
  //checkerBoard.printBoard();

  return 0;
}

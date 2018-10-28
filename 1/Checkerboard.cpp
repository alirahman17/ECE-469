#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include "CheckerBoard.hpp"
#include "piece.hpp"

using namespace std;

CheckerBoard::CheckerBoard(int load[8][8]){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      board[i][j] = load[i][j];
      if(board[i][j] == 1){
        Piece *p = new Piece(i, j, 1, 1);
        p1.push_back(p);
      } else if(board[i][j] == 2){
        Piece *p = new Piece(i, j, 2, 1);
        p1.push_back(p);
      }
    }
  }
}

void CheckerBoard::printBlack(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219 << 219 << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}
void CheckerBoard::printWhite(){
  cout << "\33[3" << 7 << ";4" << 7 << "m";
  cout << 219 << 219 << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void CheckerBoard::printP1(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 1 << ";4" << 1 << "m";
  cout << 219;
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void CheckerBoard::printP2(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 7 << ";4" << 7 << "m";
  cout << 219;
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

list <Move *> CheckerBoard::get_moves(list<Piece *> p1, list <Move *> mp, int p){
  for(list<Piece *>::iterator iter = p1.begin(); iter != p1.end(); iter++){
    if((* iter)->player == p){
      int r = (* iter)->row;
      int c = (* iter)->col;
      if((* iter)->row == 0 && (* iter)->col != 7){
        //Can't Move Up
        if(board[((* iter)->row) + 1][((* iter)->col) - 1] == 0){
          Move *m = new Move(r, c, r + 1, c - 1);
          mp.push_back(m);
        }
        if(board[((* iter)->row) + 1][((* iter)->col) + 1] == 0){
          Move *m = new Move(r, c, r + 1, c + 1);
          mp.push_back(m);
        }
      }
      else if((* iter)->row == 0 && (* iter)->col == 7){
        //Can't Move Up or Right
        if(board[((* iter)->row) + 1][((* iter)->col) + 1] == 0){
          Move *m = new Move(r, c, r + 1, c - 1);
          mp.push_back(m);
        }
      }
      else if((* iter)->row == 7 && (* iter)->col != 0){
        //Can't Move Down
        if(board[((* iter)->row) - 1][((* iter)->col) - 1] == 0){
          Move *m = new Move(r, c, r - 1, c - 1);
          mp.push_back(m);
        }
        if(board[((* iter)->row) - 1][((* iter)->col) + 1] == 0){
          Move *m = new Move(r, c, r - 1, c + 1);
          mp.push_back(m);
        }
      }
      else if((* iter)->row == 7 && (* iter)->col == 0){
        //Can't Move Down or Left
        if(board[((* iter)->row) - 1][((* iter)->col) + 1] == 0){
          Move *m = new Move(r, c, r - 1, c + 1);
          mp.push_back(m);
        }
      }
      else if((* iter)->row != 0 && (* iter)->col == 0){

      }
      else if((* iter)->row != 0 && (* iter)->col == 7){

      }
      else if((* iter)->row != 7 && (* iter)->col == 0){

      }
      else if((* iter)->row != 7 && (* iter)->col == 7){

      } else {
        //Can Move anywhere
        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(board[((* iter)->row) + 1][((* iter)->col) - 1] == 2){
              if(board[((* iter)->row) + 2][((* iter)->col) - 2] == 0){
                //Jump
                Move *m = new Move(r, c, r + 2, c - 2);
                mp.push_back(m);
              }
            }

            if(board[((* iter)->row) + 1][((* iter)->col) - 1] == 0){
              Move *m = new Move(r, c, r + 1, c - 1);
              mp.push_back(m);
            }
            if(board[((* iter)->row) + 1][((* iter)->col) + 1] == 0){
              Move *m = new Move(r, c, r + 1, c + 1);
              mp.push_back(m);
            }
          } else{
            if(board[((* iter)->row) - 1][((* iter)->col) - 1] == 0){
              Move *m = new Move(r, c, r - 1, c - 1);
              mp.push_back(m);
            }
            if(board[((* iter)->row) - 1][((* iter)->col) + 1] == 0){
              Move *m = new Move(r, c, r - 1, c + 1);
              mp.push_back(m);
            }
          }
        }
      }
    }
  }
  return mp;
}

void CheckerBoard::make_move(int m){
  if(m > 0 && m <= this->m1.size()){
    list<Move *>::iterator iter = this->m1.begin();
    advance(iter,m-1);
    cout << "Current: R" << (* iter)->cur_row << ",C" << (* iter)->cur_col << " -> R" << (* iter)->next_row << ",C" << (* iter)->next_col << endl;
    for(list<Piece *>::iterator it = this->p1.begin(); it != this->p1.end(); it++){
      if((* it)->row == (* iter)->cur_row && (* it)->col == (* iter)->cur_col){
        //cout << ++k << endl;
        int nr = (* iter)->next_row;
        int nc = (* iter)->next_col;
        int play = (* it)->player;
        int t = (* it)->type;
        cout << "NR: " << nr << ", NC: " << nc << ", PLAY: " << play << ", T: " << t << endl;
        p1.erase(it);
        Piece *p2 = new Piece(nr, nc, play, t);
        p1.push_back(p2);
        break;
      }
    }
  } else{
    cout << "Invalid Option: Pick New Move\n";
  }
}

void CheckerBoard::print_moves(int p){
  this->m1.clear();
  this->m1 = this->get_moves(this->p1, this->m1, p);
  cerr << "Moves: " << this->m1.size() << endl;

  int k = 0;
  for(list<Move *>::iterator iter = this->m1.begin(); iter != this->m1.end(); iter++){
    cout << "Option " << ++k;
    cout << ": R" << (* iter)->cur_row << ",C" << (* iter)->cur_col << " -> R" << (* iter)->next_row << ",C" << (* iter)->next_col << endl;
  }
}

void CheckerBoard::updateBoard(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      this->board[i][j] = 0;
    }
  }
  for(list<Piece *>::iterator iter = this->p1.begin(); iter != this->p1.end(); iter++){
    this->board[(* iter)->row][(* iter)->col] = (* iter)->player;
  }
}

void CheckerBoard::printBoard(){
  updateBoard();
  cout << "                                      C\n";
  cout << "      0        1        2        3        4        5        6        7\n";
  for(int i = 0; i < 8; i++){
    if(i % 2 == 1){
      for (int k = 0; k < 5; k++){
        for(int j = 0; j < 8; j++){
          if(k == 2){
            if(j == 0){
              cout << " " << i << " ";
            }
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
            if(i == 3 && j == 0 && k == 4){
              cout << "R  ";
            } else if(j == 0){
              cout << "   ";
            }
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
            if(j == 0){
              cout << " " << i << " ";
            }
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
            if(j == 0){
              cout << "   ";
            }
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

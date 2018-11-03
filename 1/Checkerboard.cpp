#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include "CheckerBoard.hpp"
#include "piece.hpp"
#include <string.h>

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

void CheckerBoard::printP1k(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 0 << ";4" << 1 << "m";
  cout << " K ";
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void CheckerBoard::printP2k(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 0 << ";4" << 7 << "m";
  cout << " K ";
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

vector<vector<int>> CheckerBoard::check_jumps(Piece* pj, vector<int> jr, vector<int> jc){
  vector<vector<int>> rowcol;
  int sz = jr.size();
  int play = pj->player;  //Piece Player
  int t = pj->type;       //Piece Type
  int orr = pj->row;      //Original Row
  int oc = pj ->col;      //Original Col
  int r = jr[jr.size() - 1];
  int c = jc[jc.size() - 1];
  int jump = 1;
  int p = play;
  bool pp = true;
  bool mp = true;
  bool pm = true;
  bool mm = true;
  if(play == p){
    int sampleBoard[8][8] = {0};
    memcpy(sampleBoard,board,sizeof(board));

    for(int k = 0; k < jr.size(); k++){

      if(k == 0){
        int dr = (jr[k] - orr)/2;
        int dc = (jc[k] - oc)/2;
        sampleBoard[orr + dr][oc + dc] = 0;
      } else{
        int dr = ( jr[k] - jr[k-1] ) / 2;
        int dc = ( jc[k] - jc[k-1] ) / 2;
        sampleBoard[jr[k-1] + dr][jc[k-1] + dc] = 0;

      }

    }

    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        if(sampleBoard[i][j] == 3){
          sampleBoard[i][j] = 1;
        }
        if(sampleBoard[i][j] == 4){
          sampleBoard[i][j] = 2;
        }
      }
    }


    if(r == 0 && c != 7){
      //Can't Move Up
      if((sampleBoard[(r) + 1][(c) - 1] == 2 )&& (c - 1) != 0 && p == 1){
        if(sampleBoard[(r) + 2][(c) - 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r+2);
          cr.push_back(c-2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if((sampleBoard[(r) + 1][(c) + 1] == 2 )&& p == 1){
        if(sampleBoard[(r) + 2][(c) + 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r+2);
          cr.push_back(c+2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if((sampleBoard[(r) + 1][(c) - 1] == 1 ) && (c - 1) != 0 && p == 2){
        if(sampleBoard[(r) + 2][(c) - 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r+2);
          cr.push_back(c-2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if((sampleBoard[(r) + 1][(c) + 1] == 1 ) && p == 2){
        if(sampleBoard[(r) + 2][(c) + 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r+2);
          cr.push_back(c+2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
    }
    else if(r == 0 && c == 7){
      //Can't Move Up or Right
      if(sampleBoard[(r) + 1][(c) - 1] == 2 && p == 1){
        if(sampleBoard[(r) + 2][(c) - 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r+2);
          cr.push_back(c-2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if(sampleBoard[(r) + 1][(c) - 1] == 1 && p == 2){
        if(sampleBoard[(r) + 2][(c) - 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r+2);
          cr.push_back(c-2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
    }
    else if(r == 7 && c != 0){
      //Can't Move Down
      if(sampleBoard[(r) - 1][(c) - 1] == 1 && p == 2){
        if(sampleBoard[(r) - 2][(c) - 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r-2);
          cr.push_back(c-2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if(sampleBoard[(r) - 1][(c) + 1] == 1 && (c + 1) != 7 && p == 2){
        if(sampleBoard[(r) - 2][(c) + 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r-2);
          cr.push_back(c+2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if(sampleBoard[(r) - 1][(c) - 1] == 2 && p == 1){
        if(sampleBoard[(r) - 2][(c) - 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r-2);
          cr.push_back(c-2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if(sampleBoard[(r) - 1][(c) + 1] == 2 && (c + 1) != 7 && p == 1){
        if(sampleBoard[(r) - 2][(c) + 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r-2);
          cr.push_back(c+2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
    }
    else if(r == 7 && c == 0){
      //Can't Move Down or Left
      if(sampleBoard[(r) - 1][(c) + 1] == 1 && p == 2){
        if(sampleBoard[(r) - 2][(c) + 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r-2);
          cr.push_back(c+2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
      if(sampleBoard[(r) - 1][(c) + 1] == 2 && p == 1){
        if(sampleBoard[(r) - 2][(c) + 2] == 0){
          vector<int> mr = jr;    //Move Row Vector
          vector<int> cr = jc;    //Move Column Vector
          mr.push_back(r-2);
          cr.push_back(c+2);
          vector<vector<int>> rc = check_jumps(pj,mr,cr);
          for(int k = 0; k < rc.size(); k++){
            rowcol.push_back(rc[k]);
          }
        }
      }
    }
    else if(r != 0 && c == 0){
      if(t == 1){
        //Regular Piece
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) + 1] == 2){
            if(sampleBoard[(r) + 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c+2);
              if((r + 2) == 7){
                //Become King No More Jumps
                rowcol.push_back(mr);
                rowcol.push_back(cr);
              } else{
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
              }
            }
          }
        } else{
          if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0){
            if(sampleBoard[(r) - 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        }
      } else{
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) + 1] == 2){
            if(sampleBoard[(r) + 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
            }
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 2 && (r - 1) != 0){
            if(sampleBoard[(r) - 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        } else{
          if(sampleBoard[(r) + 1][(c) + 1] == 1){
            if(sampleBoard[(r) + 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
            }
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0){
            if(sampleBoard[(r) - 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        }
      }


    }
    else if(r != 0 && c == 7){

      if(t == 1){
        //Regular Piece
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7){
            if(sampleBoard[(r) + 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        } else{
          if(sampleBoard[(r) - 1][(c) - 1] == 1){
            if(sampleBoard[(r) - 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c-2);
              if((r - 2) == 0){
                //Become King No More Jumps
                rowcol.push_back(mr);
                rowcol.push_back(cr);
              } else{
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
              }
            }
          }
        }
      } else{
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7){
            if(sampleBoard[(r) + 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 2){
            if(sampleBoard[(r) - 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        } else{
          if(sampleBoard[(r) + 1][(c) - 1] == 1 && (r + 1) != 7){
            if(sampleBoard[(r) + 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 1){
            if(sampleBoard[(r) - 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        }
      }

    }
    else if(r != 7 && c == 0){

      if(t == 1){
        //Regular Piece
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) + 1] == 2){


          }
        } else{
          if(sampleBoard[(r) - 1][(c) + 1] == 2){


          }
        }
      }

    }
    else if(r != 7 && c == 7){

      if(t == 1){
        //Regular Piece
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) - 1] == 2){


          }
        } else{
          if(sampleBoard[(r) - 1][(c) - 1] == 2){


          }
        }
      }

    } else {
      //Can Move anywhere
      if(t == 1){
        //Regular Piece
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7 && (c - 1) != 0){
            if(sampleBoard[(r) + 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c-2);
              if((r + 2) == 7){
                //Become King No More Jumps
                rowcol.push_back(mr);
                rowcol.push_back(cr);
              } else{
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
              }
            }
          }
          if(sampleBoard[(r) + 1][(c) + 1] == 2 && (r + 1) != 7 && (c + 1) != 7){
            if(sampleBoard[(r) + 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c+2);
              if((r + 2) == 7){
                //Become King No More Jumps
                rowcol.push_back(mr);
                rowcol.push_back(cr);
              } else{
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
              }
            }
          }
        } else{
          if(sampleBoard[(r) - 1][(c) - 1] == 1 && (r - 1) != 0 && (c - 1) != 0){
            if(sampleBoard[(r) - 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c-2);
              if((r - 2) == 0){
                //Become King No More Jumps
                rowcol.push_back(mr);
                rowcol.push_back(cr);
              } else{
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0 && (c + 1) != 7){
            if(sampleBoard[(r) - 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c+2);
              if((r - 2) == 0){
                //Become King No More Jumps
                rowcol.push_back(mr);
                rowcol.push_back(cr);
              } else{
                vector<vector<int>> rc = check_jumps(pj,mr,cr);
                for(int k = 0; k < rc.size(); k++){
                  rowcol.push_back(rc[k]);
                }
              }
            }
          }
        }
      } else{
        // King
        if(p == 1){
          if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7 && (c - 1) != 0){
            if(sampleBoard[(r) + 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) + 1][(c) + 1] == 2 && (r + 1) != 7 && (c + 1) != 7){
            if(sampleBoard[(r) + 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 2 && (r - 1) != 0 && (c - 1) != 0){
            if(sampleBoard[(r) - 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 2 && (r - 1) != 0 && (c + 1) != 7){
            if(sampleBoard[(r) - 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        } else{
          if(sampleBoard[(r) + 1][(c) - 1] == 1 && (r + 1) != 7 && (c - 1) != 0){
            if(sampleBoard[(r) + 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) + 1][(c) + 1] == 1 && (r + 1) != 7 && (c + 1) != 7){
            if(sampleBoard[(r) + 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r+2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 1 && (r - 1) != 0 && (c - 1) != 0){
            if(sampleBoard[(r) - 2][(c) - 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c-2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0 && (c + 1) != 7){
            if(sampleBoard[(r) - 2][(c) + 2] == 0){
              vector<int> mr = jr;    //Move Row Vector
              vector<int> cr = jc;    //Move Column Vector
              mr.push_back(r-2);
              cr.push_back(c+2);
              vector<vector<int>> rc = check_jumps(pj,mr,cr);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        }
      }
    }
  }
    //if rowcol empty no extra jumps
    if(rowcol.size() == 0){
      rowcol.push_back(jr);
      rowcol.push_back(jc);
      return rowcol;
    } else{
      return rowcol;
    }

}


list <Move *> CheckerBoard::get_moves(list<Piece *> p1, list <Move *> mp, int p, vector<int> jr, vector<int> jc, Piece* pj){
  int jump = 0;
  int sampleBoard[8][8] = {0};
  memcpy(sampleBoard,board,sizeof(board));

  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(sampleBoard[i][j] == 3){
        sampleBoard[i][j] = 1;
      }
      if(sampleBoard[i][j] == 4){
        sampleBoard[i][j] = 2;
      }
    }
  }


  for(list<Piece *>::iterator iter = p1.begin(); iter != p1.end(); iter++){
    vector<int> mr = jr;
    vector<int> cr = jc;
    if((* iter)->player == p){
      int r = (* iter)->row;
      int c = (* iter)->col;
      if(r == 0 && c != 7){
        //Can't Move Up
        if(sampleBoard[(r) + 1][(c) - 1] == 2 && (c - 1) != 0 && p == 1){
          if(sampleBoard[(r) + 2][(c) - 2] == 0){
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+2);
            cr.push_back(c-2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[(r) + 1][(c) + 1] == 2 && p == 1){
          if(sampleBoard[(r) + 2][(c) + 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+2);
            cr.push_back(c+2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[(r) + 1][(c) - 1] == 1 && (c - 1) != 0 && p == 2){
          if(sampleBoard[(r) + 2][(c) - 2] == 0){
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+2);
            cr.push_back(c-2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[(r) + 1][(c) + 1] == 1 && p == 2){
          if(sampleBoard[(r) + 2][(c) + 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+2);
            cr.push_back(c+2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
      }
      else if(r == 0 && c == 7){
        //Can't Move Up or Right
        if(sampleBoard[(r) + 1][(c) - 1] == 2 && p == 1){
          if(sampleBoard[(r) + 2][(c) - 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+2);
            cr.push_back(c-2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[(r) + 1][(c) - 1] == 1 && p == 2){
          if(sampleBoard[(r) + 2][(c) - 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+2);
            cr.push_back(c-2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
      }
      else if(r == 7 && c != 0){
        //Can't Move Down
        if(sampleBoard[(r) - 1][(c) - 1] == 1 && p == 2){
          if(sampleBoard[(r) - 2][(c) - 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-2);
            cr.push_back(c-2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[(r) - 1][(c) + 1] == 1 && (c + 1) != 7 && p == 2){
          if(sampleBoard[(r) - 2][(c) + 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-2);
            cr.push_back(c+2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[r - 1][(c) - 1] == 2 && p == 1){
          if(sampleBoard[(r) - 2][(c) - 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-2);
            cr.push_back(c-2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[r - 1][c + 1] == 2 && (c + 1) != 7 && p == 1){
          if(sampleBoard[(r) - 2][(c) + 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-2);
            cr.push_back(c+2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
      }
      else if(r == 7 && c == 0){
        //Can't Move Down or Left
        if(sampleBoard[(r) - 1][(c) + 1] == 1 && p == 2){
          if(sampleBoard[(r) - 2][(c) + 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-2);
            cr.push_back(c+2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
        if(sampleBoard[(r) - 1][(c) + 1] == 2 && p == 1){
          if(sampleBoard[(r) - 2][(c) + 2] == 0){
            //Jump True
            jump = 1;
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-2);
            cr.push_back(c+2);
            vector<vector<int>> rc = check_jumps(*iter,mr,cr);
            for(int k = 0; k < rc.size(); k+=2){
              Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
              mp.push_back(m);
            }
          }
        }
      }
      else if(r != 0 && c == 0){
        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) + 1] == 2){
              if(sampleBoard[(r) + 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r+2);
                cr.push_back(c+2);
                if((r + 2) == 7){
                  //Become King No More Jumps
                  Move *m = new Move(r,c,r,c,mr,cr);
                  mp.push_back(m);
                } else{
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
                }
              }
            }
          } else{
            if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0){
              if(sampleBoard[(r) - 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r-2);
                cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
          }
        } else{
          //king
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) + 1] == 2){
              if(sampleBoard[(r) + 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r+2);
                cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
            if(sampleBoard[(r) - 1][(c) + 1] == 2 && (r - 1) != 0){
              if(sampleBoard[(r) - 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r-2);
                cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
          } else{
            if(sampleBoard[(r) + 1][(c) + 1] == 1){
              if(sampleBoard[(r) + 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r+2);
                cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
            if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0){
              if(sampleBoard[(r) - 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r-2);
                cr.push_back(c+2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
          }

        }


      }
      else if(r != 0 && c == 7){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7){
              if(sampleBoard[(r) + 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r+2);
                cr.push_back(c-2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
          } else{
            if(sampleBoard[(r) - 1][(c) - 1] == 1){
              if(sampleBoard[(r) - 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r-2);
                cr.push_back(c-2);
                if((r - 2) == 0){
                  //Become King No More Jumps
                  Move *m = new Move(r,c,r,c,mr,cr);
                  mp.push_back(m);
                } else{
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
                }
              }
            }
          }
        } else{
          //king
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7){
              if(sampleBoard[(r) + 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r+2);
                cr.push_back(c-2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
            if(sampleBoard[(r) - 1][(c) - 1] == 2){
              if(sampleBoard[(r) - 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r-2);
                cr.push_back(c-2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
          }
        } else{
            if(sampleBoard[(r) + 1][(c) - 1] == 1 && (r + 1) != 7){
              if(sampleBoard[(r) + 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r+2);
                cr.push_back(c-2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
            if(sampleBoard[(r) - 1][(c) - 1] == 1){
              if(sampleBoard[(r) - 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                vector<int> mr = jr;
                vector<int> cr = jc;
                mr.push_back(r-2);
                cr.push_back(c-2);
                vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                for(int k = 0; k < rc.size(); k+=2){
                  Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                  mp.push_back(m);
                }
              }
            }
          }
      }
    }
      else if(r != 7 && c == 0){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) + 1] == 2){


            }
          } else{
            if(sampleBoard[(r) - 1][(c) + 1] == 2){


            }
          }
        }

      }
      else if(r != 7 && c == 7){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 2){


            }
          } else{
            if(sampleBoard[(r) - 1][(c) - 1] == 2){


            }
          }
        }

      } else {
        //Can Move anywhere
        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7 && (c - 1) != 0){
              if(sampleBoard[(r) + 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                if((r + 2) == 7){
                  //Become King No More Jumps
                  mr.push_back(r+2);
                  cr.push_back(c-2);
                  Move *m = new Move(r,c,r,c,mr,cr);
                  mp.push_back(m);
                } else{
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r+2);
                  cr.push_back(c-2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
                }
              }
            }
            if(sampleBoard[(r) + 1][(c) + 1] == 2 && (r + 1) != 7 && (c + 1) != 7){
              if(sampleBoard[(r) + 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                if((r + 2) == 7){
                  //Become King No More Jumps
                  mr.push_back(r+2);
                  cr.push_back(c+2);
                  Move *m = new Move(r,c,r,c,mr,cr);
                  mp.push_back(m);
                } else{
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r+2);
                  cr.push_back(c+2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
                }
              }
            }
          } else{
            if(sampleBoard[(r) - 1][(c) - 1] == 1 && (r - 1) != 0 && (c - 1) != 0){
              if(sampleBoard[(r) - 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                if((r - 2) == 0){
                  //Become King No More Jumps
                  mr.push_back(r-2);
                  cr.push_back(c-2);
                  Move *m = new Move(r,c,r,c,mr,cr);
                  mp.push_back(m);
                } else{
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r-2);
                  cr.push_back(c-2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
                }
              }
            }
            if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0 && (c + 1) != 7){
              if(sampleBoard[(r) - 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                if((r - 2) == 0){
                  //Become King No More Jumps
                  mr.push_back(r-2);
                  cr.push_back(c+2);
                  Move *m = new Move(r,c,r,c,mr,cr);
                  mp.push_back(m);
                } else{
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r-2);
                  cr.push_back(c+2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
                }
              }
            }
          }
        } else{
          // king
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 2 && (r + 1) != 7 && (c - 1) != 0){
              if(sampleBoard[(r) + 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r+2);
                  cr.push_back(c-2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
            if(sampleBoard[(r) + 1][(c) + 1] == 2 && (r + 1) != 7 && (c + 1) != 7){
              if(sampleBoard[(r) + 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r+2);
                  cr.push_back(c+2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
            if(sampleBoard[(r) - 1][(c) - 1] == 2 && (r - 1) != 0 && (c - 1) != 0){
              if(sampleBoard[(r) - 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r-2);
                  cr.push_back(c-2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
            if(sampleBoard[(r) - 1][(c) + 1] == 2 && (r - 1) != 0 && (c + 1) != 7){
              if(sampleBoard[(r) - 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r-2);
                  cr.push_back(c+2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
          } else{
            if(sampleBoard[(r) + 1][(c) - 1] == 1 && (r + 1) != 7 && (c - 1) != 0){
              if(sampleBoard[(r) + 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r+2);
                  cr.push_back(c-2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
            if(sampleBoard[(r) + 1][(c) + 1] == 1 && (r + 1) != 7 && (c + 1) != 7){
              if(sampleBoard[(r) + 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r+2);
                  cr.push_back(c+2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
            if(sampleBoard[(r) - 1][(c) - 1] == 1 && (r - 1) != 0 && (c - 1) != 0){
              if(sampleBoard[(r) - 2][(c) - 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r-2);
                  cr.push_back(c-2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
            if(sampleBoard[(r) - 1][(c) + 1] == 1 && (r - 1) != 0 && (c + 1) != 7){
              if(sampleBoard[(r) - 2][(c) + 2] == 0){
                //Jump
                jump = 1;
                  vector<int> mr = jr;
                  vector<int> cr = jc;
                  mr.push_back(r-2);
                  cr.push_back(c+2);
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr);
                  for(int k = 0; k < rc.size(); k+=2){
                    Move *m = new Move(r, c, r + 1, c - 1, rc[k], rc[k+1]);
                    mp.push_back(m);
                  }
              }
            }
          }




        }
      }
    }
  }

  if(jump == 1){
    return mp;
  }

  for(list<Piece *>::iterator iter = p1.begin(); iter != p1.end(); iter++){
    if((* iter)->player == p){
      int r = (* iter)->row;
      int c = (* iter)->col;
      if(r == 0 && c != 7){
        //Can't Move Up
        if(sampleBoard[(r) + 1][(c) - 1] == 0){
          vector<int> mr = jr;
          vector<int> cr = jc;
          mr.push_back(r+1);
          cr.push_back(c-1);
          Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
          mp.push_back(m);
        }
        if(sampleBoard[(r) + 1][(c) + 1] == 0){
          vector<int> mr = jr;
          vector<int> cr = jc;
          mr.push_back(r+1);
          cr.push_back(c+1);
          Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
          mp.push_back(m);
        }
      }
      else if(r == 0 && c == 7){
        //Can't Move Up or Right
        if(sampleBoard[(r) + 1][(c) - 1] == 0){
          vector<int> mr = jr;
          vector<int> cr = jc;
          mr.push_back(r+1);
          cr.push_back(c-1);
          Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
          mp.push_back(m);
        }
      }
      else if(r == 7 && c != 0){
        //Can't Move Down
        if(sampleBoard[(r) - 1][(c) - 1] == 0){
          vector<int> mr = jr;
          vector<int> cr = jc;
          mr.push_back(r-1);
          cr.push_back(c-1);
          Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
          mp.push_back(m);
        }
        if(sampleBoard[(r) - 1][(c) + 1] == 0){
          vector<int> mr = jr;
          vector<int> cr = jc;
          mr.push_back(r-1);
          cr.push_back(c+1);
          Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
          mp.push_back(m);
        }
      }
      else if(r == 7 && c == 0){
        //Can't Move Down or Left
        if(sampleBoard[(r) - 1][(c) + 1] == 0){
          vector<int> mr = jr;
          vector<int> cr = jc;
          mr.push_back(r-1);
          cr.push_back(c+1);
          Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
          mp.push_back(m);
        }
      }
      else if(r != 0 && c == 0){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) + 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r+1);
              cr.push_back(c+1);
              Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
              mp.push_back(m);
            }
          } else{
            if(sampleBoard[(r) - 1][(c) + 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r-1);
              cr.push_back(c+1);
              Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
              mp.push_back(m);
            }
          }
        } else{
          if(sampleBoard[(r) + 1][(c) + 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+1);
            cr.push_back(c+1);
            Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-1);
            cr.push_back(c+1);
            Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
            mp.push_back(m);
          }
        }


      }
      else if(r != 0 && c == 7){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r+1);
              cr.push_back(c-1);
              Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
              mp.push_back(m);
            }
          } else{
            if(sampleBoard[(r) - 1][(c) - 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r-1);
              cr.push_back(c-1);
              Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
              mp.push_back(m);
            }
          }
        } else{
          if(sampleBoard[(r) + 1][(c) - 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+1);
            cr.push_back(c-1);
            Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-1);
            cr.push_back(c-1);
            Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
            mp.push_back(m);
          }
        }

      }
      else if(r != 7 && c == 0){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) + 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r+1);
              cr.push_back(c+1);
              Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
              mp.push_back(m);
            }
          } else{
            if(sampleBoard[(r) - 1][(c) + 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r-1);
              cr.push_back(c+1);
              Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
              mp.push_back(m);
            }
          }
        } else{
          if(sampleBoard[(r) + 1][(c) + 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+1);
            cr.push_back(c+1);
            Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-1);
            cr.push_back(c+1);
            Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
            mp.push_back(m);
          }
        }

      }
      else if(r != 7 && c == 7){

        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r+1);
              cr.push_back(c-1);
              Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
              mp.push_back(m);
            }
          } else{
            if(sampleBoard[(r) - 1][(c) - 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r-1);
              cr.push_back(c-1);
              Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
              mp.push_back(m);
            }
          }
        } else{
          //King
          if(sampleBoard[(r) + 1][(c) - 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+1);
            cr.push_back(c-1);
            Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-1);
            cr.push_back(c-1);
            Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
            mp.push_back(m);
          }
        }

      } else {
        //Can Move anywhere
        if((* iter)->type == 1){
          //Regular Piece
          if(p == 1){
            if(sampleBoard[(r) + 1][(c) - 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r+1);
              cr.push_back(c-1);
              Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
              mp.push_back(m);
            }
            if(sampleBoard[(r) + 1][(c) + 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r+1);
              cr.push_back(c+1);
              Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
              mp.push_back(m);
            }
          } else{
            if(sampleBoard[(r) - 1][(c) - 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r-1);
              cr.push_back(c-1);
              Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
              mp.push_back(m);
            }
            if(sampleBoard[(r) - 1][(c) + 1] == 0){
              vector<int> mr = jr;
              vector<int> cr = jc;
              mr.push_back(r-1);
              cr.push_back(c+1);
              Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
              mp.push_back(m);
            }
          }
        } else{
          //King
          if(sampleBoard[(r) + 1][(c) - 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+1);
            cr.push_back(c-1);
            Move *m = new Move(r, c, r + 1, c - 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) + 1][(c) + 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r+1);
            cr.push_back(c+1);
            Move *m = new Move(r, c, r + 1, c + 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) - 1][(c) - 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-1);
            cr.push_back(c-1);
            Move *m = new Move(r, c, r - 1, c - 1, mr, cr);
            mp.push_back(m);
          }
          if(sampleBoard[(r) - 1][(c) + 1] == 0){
            vector<int> mr = jr;
            vector<int> cr = jc;
            mr.push_back(r-1);
            cr.push_back(c+1);
            Move *m = new Move(r, c, r - 1, c + 1, mr, cr);
            mp.push_back(m);
          }
        }
      }
    }
  }
  return mp;
}

Piece * CheckerBoard::findPiece(int r, int c, list<Piece *> p){
  for(list<Piece *>::iterator iter = p.begin(); iter != p.end(); iter++){
    if((*iter)->row == r && (*iter)->col == c){
      return *iter;
    }
  }
}


void CheckerBoard::make_move(int m){
  if(m > 0 && m <= this->m1.size()){
    list<Move *>::iterator iter = this->m1.begin();
    advance(iter,m-1);
    for(list<Piece *>::iterator it = this->p1.begin(); it != this->p1.end(); it++){
      if((* it)->row == (* iter)->cur_row && (* it)->col == (* iter)->cur_col){
        //cout << ++k << endl;
        int nr = (* iter)->mrow[(* iter)->mrow.size()-1];
        int nc = (* iter)->mcol[(* iter)->mcol.size()-1];
        int play = (* it)->player;
        int t = (* it)->type;
        //Delete any pieces between
        if( abs(nr - (* iter)->cur_row) != 1){
          for(int k = 0; k < (* iter)->mcol.size(); k ++){

            if(k == 0){
              int dr = ((* iter)->mrow[k] - (* iter)->cur_row)/2;
              int dc = ((* iter)->mcol[k] - (* iter)->cur_col)/2;
              Piece* tmp = findPiece((* iter)->cur_row + dr, (* iter)->cur_col + dc,p1);
              //cout << "R" << (* iter)->cur_row + dr << ",C" << (* iter)->cur_col + dc << endl;
              p1.remove(tmp);
            } else{
              int dr = ( (* iter)->mrow[k] - (* iter)->mrow[k-1] ) / 2;
              int dc = ( (* iter)->mcol[k] - (* iter)->mcol[k-1] ) / 2;
              Piece* tmp2 = findPiece((* iter)->mrow[k-1] + dr, (* iter)->mcol[k-1] + dc,p1);
              p1.remove(tmp2);

            }

          }
        }
        if(play == 1 && nr == 7){
          t = 2;
        }
        if(play == 2 && nr == 0){
          t = 2;
        }
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

int CheckerBoard::print_moves(int p){
  this->m1.clear();
  vector<int> rows;
  vector<int> cols;
  Piece *pj = new Piece(0,0,0,0);
  this->m1 = this->get_moves(this->p1, this->m1, p, rows, cols, pj);
  cout << "Moves: " << this->m1.size() << endl;
  int z = 0;
  for(list<Move *>::iterator iter = this->m1.begin(); iter != this->m1.end(); iter++){
    cout << "Option " << ++z;
    cout << ": R" << (* iter)->cur_row << ",C" << (* iter)->cur_col;
    for(int k = 0; k < (* iter)->mrow.size(); k++){
      cout << " -> R" << (* iter)->mrow[k] << ",C" << (* iter)->mcol[k];
    }
    cout << endl;
  }
  return z;
}

void CheckerBoard::updateBoard(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      this->board[i][j] = 0;
    }
  }
  for(list<Piece *>::iterator iter = this->p1.begin(); iter != this->p1.end(); iter++){
    if((* iter)->player == 1){
      if((* iter)->type == 1){
        this->board[(* iter)->row][(* iter)->col] = 1;
      } else{
        this->board[(* iter)->row][(* iter)->col] = 3;
      }
    } else{
      if((* iter)->type == 1){
        this->board[(* iter)->row][(* iter)->col] = 2;
      } else{
        this->board[(* iter)->row][(* iter)->col] = 4;
      }
    }
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
            else if(board[i][j] == 3){
              printP1k();
            }
            else if(board[i][j] == 4){
              printP2k();
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
            else if(board[i][j] == 3){
              printP1k();
            }
            else if(board[i][j] == 4){
              printP2k();
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

#include <iostream>
#include <iterator>
#include <list>
#include <ctime>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include "CheckerBoard.hpp"
#include "piece.hpp"
#include <string.h>
#include <climits>

using namespace std;

static int  fg_c = 9;
static int  bg_c = 9;
#define set_colors( fg, bg ) cout << "\33[3" << (fg_c = fg) << ";4" << (bg_c = bg) << "m"

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
      } else if(board[i][j] == 3){
        Piece *p = new Piece(i, j, 1, 2);
        p1.push_back(p);
      } else if(board[i][j] == 4){
        Piece *p = new Piece(i, j, 2, 2);
        p1.push_back(p);
      }
    }
  }
}

int CheckerBoard::AlphaBeta(int depth, int Alpha, int Beta, list<Piece *> pi, int p, double timeRemaining, double startTime, double stoptime, int odepth, time_t tm1){
  int m1 = 0;
  for(list<Piece *>::iterator iter2 = pi.begin(); iter2 != pi.end(); iter2++){
    if((*iter2) ->player == 2){
      m1++;
    }
  }
  vector <int> rando;
  vector<int> mr;
  vector<int> mc;
  if(depth == 0 || m1 == 0){
    if(p == 2){
      return evaluate_move(pi);
    } else{
      return evaluate_move(pi);
    }
  }
  int p2 = 0;
  list<Move*> mv = get_moves(pi, p, mr, mc);
  mr.clear();
  mc.clear();
  int x = 1;
  if(mv.size() == 1 && depth == odepth){
    aimove.clear();
    aimove.push_back(1);
    return Alpha;
  }

  if(p == 1){
    p2 = 2;
    for(int i = 0; i < mv.size(); i++){
      list <Piece *> pk = sample_move(i,mv,pi);
      clock_t t2 = clock();
      time_t tm2 = time(0);
      if(((double)t2 - startTime)/(CLOCKS_PER_SEC) > 0.8*(stoptime)){
        double q = difftime(tm2,tm1);
        //cout << "Computer Took: " << q << "second(s) Calendar Time" << endl;
        return INT_MAX;
      }
      int tmp = AlphaBeta(depth-1, Alpha, Beta, pk, p2, ((double)t2 - startTime)/(CLOCKS_PER_SEC), startTime, stoptime, odepth, tm1);
      if(tmp == INT_MAX){
        return INT_MAX;
      }
      if(Beta > tmp){
        x = i+1;
        rando.clear();
        rando.push_back(x);
        Beta = tmp;
      }
      if(Beta == tmp){
        rando.push_back(i+1);
      }
      if(Beta <= Alpha){
        break;
      }
    }
    if(depth == odepth){
      aimove.clear();
      int y = rand() % rando.size();
      aimove.push_back(rando[y]);
    }
    return Beta;
  } else{
    p2 = 1;
    for(int i = 0; i < mv.size(); i++){
      list <Piece *> pk = sample_move(i,mv,pi);
      clock_t t2 = clock();
      time_t tm2 = time(0);
      if(((double)t2 - startTime)/(CLOCKS_PER_SEC) > 0.8*(stoptime)){
        double q = (double)difftime(tm2,tm1);
        //cout << "Computer Took: " << q << "second(s) Calendar Time" << endl;
        //cout << "TIME LIMIT\n";
        return INT_MAX;
      }
      int tmp = AlphaBeta(depth-1, Alpha, Beta, pk, p2, ((double)t2 - startTime)/(CLOCKS_PER_SEC), startTime, stoptime, odepth, tm1);
      if(tmp == INT_MAX){
        return INT_MAX;
      }
      if(Alpha < tmp){
        x = i+1;
        rando.clear();
        rando.push_back(x);
        Alpha = tmp;
      }
      if(Beta == tmp){
        rando.push_back(i+1);
      }
      if(Beta <= Alpha){
        break;
      }
    }
    if(depth == odepth){
      aimove.clear();
      int y = rand() % rando.size();
      aimove.push_back(rando[y]);
    }
    return Alpha;
  }

}

int CheckerBoard::AlphaBeta2(int depth, int Alpha, int Beta, list<Piece *> pi, int p, double timeRemaining, double startTime, double stoptime, int odepth){
  int m1 = 0;
  for(list<Piece *>::iterator iter2 = pi.begin(); iter2 != pi.end(); iter2++){
    if((*iter2) ->player == 2){
      m1++;
    }
  }

  vector<int> mr;
  vector<int> mc;
  if(depth == 0 || m1 == 0){
    if(p == 2){
      return -evaluate_move(pi);
    } else{
      return -evaluate_move(pi);
    }
  }
  int p2 = 0;
  int best = 0;
  list<Move*> mv = get_moves(pi, p, mr, mc);
  mr.clear();
  mc.clear();
  int x = 1;
  if(mv.size() == 1 && depth == odepth){
    aimove.clear();
    aimove.push_back(1);
    return Alpha;
  }

  if(p == 1){
    p2 = 2;
    for(int i = 0; i < mv.size(); i++){
      list <Piece *> pk = sample_move(i,mv,pi);
      clock_t t2 = clock();
      if(((double)t2 - startTime)/(CLOCKS_PER_SEC) > 0.8*(stoptime)){
        return INT_MAX;
      }
      int tmp = AlphaBeta2(depth-1, Alpha, Beta, pk, p2, ((double)t2 - startTime)/(CLOCKS_PER_SEC), startTime, stoptime, odepth);
      if(tmp == INT_MAX){
        return INT_MAX;
      }
      if(Beta > tmp){
        x = i+1;
        Beta = tmp;
      }
      if(Beta <= Alpha){
        break;
      }
    }
    if(depth == odepth){
      aimove.clear();
      aimove.push_back(x);
    }
    return Beta;
  } else{
    p2 = 1;
    for(int i = 0; i < mv.size(); i++){
      list <Piece *> pk = sample_move(i,mv,pi);
      clock_t t2 = clock();
      if(((double)t2 - startTime)/(CLOCKS_PER_SEC) > 0.8*(stoptime)){
        //cout << "TIME LIMIT\n";
        return INT_MAX;
      }
      int tmp = AlphaBeta2(depth-1, Alpha, Beta, pk, p2, ((double)t2 - startTime)/(CLOCKS_PER_SEC), startTime, stoptime, odepth);
      if(tmp == INT_MAX){
        return INT_MAX;
      }
      if(Alpha < tmp){
        x = i+1;
        Alpha = tmp;
      }
      if(Beta <= Alpha){
        break;
      }
    }
    if(depth == odepth){
      aimove.clear();
      aimove.push_back(x);
    }
    return Alpha;
  }

}



int CheckerBoard::ai_move(double timeRemaining, int p){
  clock_t startTime = clock();
  time_t tm1 = time(0);
  time_t tm2;
  clock_t t2;
  int n = 1;
  int moveval = 0;
  vector<int> mr,mc;
  list<Move*> mv = get_moves(this->p1, p, mr, mc);
  if(mv.size() == 0){
    return 0;
  }
  if(p == 2){
    while((((((double)t2 - startTime)/(CLOCKS_PER_SEC)) < (0.7 * timeRemaining) || n == 1 ) && n < 35)){
      moveval = AlphaBeta(n,-500000,500000, this->p1, p, timeRemaining, (double)startTime, timeRemaining, n, tm1);
      t2 = clock();
      tm2 = time(0);
      n++;
      if(moveval == 8000){
        // Win
        break;
      }
    }
  } else{
    while((((((double)t2 - startTime)/(CLOCKS_PER_SEC)) < (0.7 * timeRemaining) || n == 1 ) && n < 35)){
      moveval = AlphaBeta2(n,-500000,500000, this->p1, p, timeRemaining, (double)startTime, timeRemaining, n);
      t2 = clock();
      tm2 = time(0);
      n++;
    }
  }

  double q = difftime(tm2,tm1);
  cout << "Computer Took: " << q << " second(s) Calendar Time" << endl;
  double timeDiff = ((double) (t2 - startTime)) / CLOCKS_PER_SEC;
  cout << "Computer Took " << timeDiff << " second(s) CPU Time and reached Depth " << n << endl;
  return aimove[0];
}

int CheckerBoard::evaluate_move(list<Piece *> pi){
  int t = 0;
  int t2 = 0;
  int t3 = 0;
  int t4 = 0;
  int m1 = 0;
  int m2 = 0;
  int k1a = 0;
  int k2a = 0;
  int k1b = 0;
  int k2b = 0;
  for(list<Piece *>::iterator iter2 = this->p1.begin(); iter2 != this->p1.end(); iter2++){
    if((*iter2) ->player == 2){
      t3 += heuristicBoard[(*iter2)->row][(*iter2)->col];
      m2++;
      if((*iter2) ->type == 2){
        k2a++;
      }
    }
    if((*iter2) ->player == 1){
      t4++;
      if((*iter2) ->type == 2){
        k1a++;
      }
    }

  }


  for(list<Piece *>::iterator iter2 = pi.begin(); iter2 != pi.end(); iter2++){
    if((*iter2) ->player == 2){
      t += heuristicBoard[(*iter2)->row][(*iter2)->col];
      m1++;
      if((*iter2) ->type == 2){
        k2b++;
      }
    }
    if((*iter2) ->player == 1){
      t2++;
      if((*iter2) ->type == 2){
        k1b++;
      }
    }
  }
  /*
  if(k2a == 2 && k1a == 1){
    //2 Kings Advantage
    t = 0;
    int r = 0;
    int c = 0;
    for(list<Piece *>::iterator iter2 = this->p1.begin(); iter2 != this->p1.end(); iter2++){
      if((*iter2) ->player == 1){
        r = (*iter2) ->row;
        c = (*iter2) ->col;
      }
    }
    if(r == 6 && c == 7){
      //H7
      for(list<Piece *>::iterator iter2 = this->p1.begin(); iter2 != this->p1.end(); iter2++){
        if((*iter2) ->player == 2){
          if((*iter2) ->row == 6 && (*iter2) ->col == 5){
            t+=1500;
          }
          if(((*iter2) ->row == 6 && (*iter2) ->col == 3) || ((*iter2) ->row == 4 && (*iter2) ->col == 5)){
            t+=1500;
          }
        }
      }
    }
    if(r == 7 && c == 6){
      //G8
      for(list<Piece *>::iterator iter2 = this->p1.begin(); iter2 != this->p1.end(); iter2++){
        if((*iter2) ->player == 2){
          if((*iter2) ->row == 5 && (*iter2) ->col == 6){
            t+=1500;
          }
          if(((*iter2) ->row == 5 && (*iter2) ->col == 4) || ((*iter2) ->row == 3 && (*iter2) ->col == 6)){
            t+=1500;
          }
        }
      }
    }
    if(r == 0 && c == 1){
      //B1
    }
    if(r == 1 && c == 0){
      //A2
    }
  }*/
  if(m1 == 0){
    t = -5000;
  }
  if(t4 == 0){
    t = 8000;
  }

  if((k2a-k2b) < 0){
    t+= (k2b-k2a)*50;
  } else{
    t+= (k2b-k2a)*175;
  }
  if((k1a-k1b) < 0){
    t+= (k1a-k1b)*200;
  } else{

  }
  t-= ((m2-m1)*100);
  t+= ((t4-t2)*75);

  return t;
}

list <Piece *> CheckerBoard::sample_move(int m, list <Move *> mn, list <Piece *> pn){
  list <Move *> mx = mn;
  list <Piece *> px = pn;
    list<Move *>::iterator iter = mx.begin();
    advance(iter,m);
    for(list<Piece *>::iterator it = px.begin(); it != px.end(); it++){
      if((* it)->row == (* iter)->cur_row && (* it)->col == (* iter)->cur_col){
        int nr = (* iter)->mrow[(* iter)->mrow.size()-1];
        int nc = (* iter)->mcol[(* iter)->mcol.size()-1];
        int play = (* it)->player;
        int t = (* it)->type;
        if( abs(nr - (* iter)->cur_row) != 1){
          for(int k = 0; k < (* iter)->mcol.size(); k ++){

            if(k == 0){
              int dr = ((* iter)->mrow[k] - (* iter)->cur_row)/2;
              int dc = ((* iter)->mcol[k] - (* iter)->cur_col)/2;
              Piece* tmp = findPiece((* iter)->cur_row + dr, (* iter)->cur_col + dc,px);
              px.remove(tmp);
            } else{
              int dr = ( (* iter)->mrow[k] - (* iter)->mrow[k-1] ) / 2;
              int dc = ( (* iter)->mcol[k] - (* iter)->mcol[k-1] ) / 2;
              Piece* tmp2 = findPiece((* iter)->mrow[k-1] + dr, (* iter)->mcol[k-1] + dc,px);
              px.remove(tmp2);
            }
          }
        }
        if(play == 1 && nr == 7){
          t = 2;
        }
        if(play == 2 && nr == 0){
          t = 2;
        }
        px.erase(it);
        Piece *p2 = new Piece(nr, nc, play, t);
        px.push_back(p2);
        break;
      }
    }
    return px;
}

void CheckerBoard::printTestBoard(list<Piece *> pk){

  int sampleBoard[8][8] = {0};

  for(list<Piece *>::iterator iter = pk.begin(); iter != pk.end(); iter++){
    if((* iter)->player == 1){
      if((* iter)->type == 1){
        sampleBoard[(* iter)->row][(* iter)->col] = 1;
      } else{
        sampleBoard[(* iter)->row][(* iter)->col] = 3;
      }
    } else{
      if((* iter)->type == 1){
        sampleBoard[(* iter)->row][(* iter)->col] = 2;
      } else{
        sampleBoard[(* iter)->row][(* iter)->col] = 4;
      }
    }
  }

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
            if(sampleBoard[i][j] == 1){
              printP1();
            }
            else if(sampleBoard[i][j] == 2){
              printP2();
            }
            else if(sampleBoard[i][j] == 3){
              printP1k();
            }
            else if(sampleBoard[i][j] == 4){
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
            if(sampleBoard[i][j] == 1){
              printP1();
            }
            else if(sampleBoard[i][j] == 2){
              printP2();
            }
            else if(sampleBoard[i][j] == 3){
              printP1k();
            }
            else if(sampleBoard[i][j] == 4){
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
  cout << "\33[3" << 7 << ";4" << 1 << "m";
  cout << "\33[1m";
  cout << " O ";
  cout << "\33[0m";
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

void CheckerBoard::printP2k(){
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 4 << ";4" << 7 << "m";
  cout << " O ";
  cout << "\33[3" << 0 << ";4" << 0 << "m";
  cout << 219;
  cout << "\33[3" << 9 << ";4" << 9 << "m";
}

vector<vector<int>> CheckerBoard::check_jumps(Piece* pj, vector<int> jr, vector<int> jc, int tboard[8][8]){
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
  if(play == p){
    int sampleBoard[8][8] = {0};
    memcpy(sampleBoard,tboard,sizeof(board));

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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
          vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
              for(int k = 0; k < rc.size(); k++){
                rowcol.push_back(rc[k]);
              }
            }
          }
        }
      }

    }
    else {
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
                vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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
              vector<vector<int>> rc = check_jumps(pj,mr,cr,board);
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


list <Move *> CheckerBoard::get_moves(list<Piece *> p1, int p, vector<int> jr, vector<int> jc){
  int jump = 0;
  int sampleBoard[8][8] = {0};

  list <Move *> mp;

  for(list<Piece *>::iterator iter = p1.begin(); iter != p1.end(); iter++){
    if((* iter)->player == 1){
      if((* iter)->type == 1){
        sampleBoard[(* iter)->row][(* iter)->col] = 1;
      } else{
        sampleBoard[(* iter)->row][(* iter)->col] = 3;
      }
    } else{
      if((* iter)->type == 1){
        sampleBoard[(* iter)->row][(* iter)->col] = 2;
      } else{
        sampleBoard[(* iter)->row][(* iter)->col] = 4;
      }
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
            vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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
                  vector<vector<int>> rc = check_jumps(*iter,mr,cr,sampleBoard);
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


int CheckerBoard::make_move(int m){
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
    return 0;
  } else{
    cout << "Invalid Option: Pick New Move\n";
    return -1;
  }
}

int CheckerBoard::print_moves(int p){
  this->m1.clear();
  vector<int> rows;
  vector<int> cols;
  Piece *pj = new Piece(0,0,0,0);
  this->m1 = this->get_moves(this->p1, p, rows, cols);
  cout << "Moves: " << this->m1.size() << endl;
  int z = 0;
  for(list<Move *>::iterator iter = this->m1.begin(); iter != this->m1.end(); iter++){
    cout << "Option " << ++z;
    string s1;
if((* iter)->cur_col == 1)
      s1 = "B";
    else if((* iter)->cur_col == 2)
      s1 = "C";
    else if((* iter)->cur_col == 3)
      s1 = "D";
    else if((* iter)->cur_col == 4)
      s1 = "E";
    else if((* iter)->cur_col == 5)
      s1 = "F";
    else if((* iter)->cur_col == 6)
      s1 = "G";
    else if((* iter)->cur_col == 7)
      s1 = "H";
    else
      s1 = "A";
    cout << ": " << s1 << (* iter)->cur_row + 1;
    for(int k = 0; k < (* iter)->mrow.size(); k++){
      string s2;
      if((* iter)->mcol[k] == 1)
        s2 = "B";
      else if((* iter)->mcol[k] == 2)
        s2 = "C";
      else if((* iter)->mcol[k] == 3)
        s2 = "D";
      else if((* iter)->mcol[k] == 4)
        s2 = "E";
      else if((* iter)->mcol[k] == 5)
        s2 = "F";
      else if((* iter)->mcol[k] == 6)
        s2 = "G";
      else if((* iter)->mcol[k] == 7)
        s2 = "H";
      else
        s2 = "A";
      cout << " -> " << s2 << (* iter)->mrow[k]+1;
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
  cout << "                                       Col\n";
  set_colors(6 , 9 );
  cout << "\33[1m";
  cout << "        A        B        C        D        E        F        G        H\n";
  set_colors(9 , 9 );
  cout << "   __________________________________________________________________________\n";
  cout << "\33[0m";
  for(int i = 0; i < 8; i++){
    if(i % 2 == 1){
      for (int k = 0; k < 5; k++){
        for(int j = 0; j < 8; j++){
          if(k == 2){
            if(j == 0){
              set_colors(6 , 9);
              cout << "\33[1m";
              cout << " " << i+1;
              set_colors(9 , 9);
              cout << " |";
              cout << "\33[0m";
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
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
            }
            else {
              printBlack();
            }
          } else{
            if(i == 3 && j == 0 && k == 4){
              cout << "\33[1m";
              cout << "R  |";
              cout << "\33[0m";
            } else if(j == 0){
              cout << "\33[1m";
              cout << "   |";
              cout << "\33[0m";
            }
            if(j % 2 == 1){
              printWhite();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
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
              set_colors(6 , 9 );
              cout << "\33[1m";
              cout << " " << i+1;
              set_colors(9 , 9 );
              cout << " |";
              cout << "\33[0m";
            }
            if(board[i][j] == 1){
              printP1();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
            }
            else if(board[i][j] == 2){
              printP2();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
            }
            else if(board[i][j] == 3){
              printP1k();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
            }
            else if(board[i][j] == 4){
              printP2k();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
            }
            else if(j % 2 == 1){
              printBlack();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
            }
            else {
              printWhite();
            }
          } else{
            if(j == 0){
              cout << "\33[1m";
              cout << "   |";
              cout << "\33[0m";
            }
            if(j % 2 == 1){
              printBlack();
              if(j == 7){
                cout << "\33[1m";
                cout << "|";
                cout << "\33[0m";
              }
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
  cout << "\33[1m";
  cout << "   __________________________________________________________________________\n";
  cout << "\33[0m";
  set_colors(9 , 9 );
}

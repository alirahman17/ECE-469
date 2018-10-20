#ifndef _CHECKERBOARD_H
#define _CHECKERBOARD_H

class CheckerBoard {
  public:
    //CheckerBoard();
    void initBoard();
    void printBoard();

  private:
    int **arr;
    int row = 8, col = 8;
};

#endif

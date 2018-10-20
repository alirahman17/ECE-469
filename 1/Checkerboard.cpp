#include <iostream>
#include "CheckerBoard.h"

using namespace std;

/*Color::Modifier m_red(Color::FG_RED);
Color::Modifier m_green(Color::FG_GREEN);
Color::Modifier m_def(Color::FG_DEFAULT);
*/
void CheckerBoard::initBoard(){
  arr = (int **)malloc(row * sizeof(int *));
	    for (int i=0; i<row; i++){
	    	arr[i] = (int *)malloc(col * sizeof(int));
	    }
}

void CheckerBoard::printBoard(){
  cout << "_________________" << endl;
	for(int i = 0; i < row; i++){
		for(int j = 0; j < col; j++){
			cout << "|";
			switch(arr[i][j]){
				case 0:
					cout << " ";
					break;
				case 1:
					cout << "*";
					break;
				case 2:
					cout << "*";
					break;
				case 3:
					cout<< "O";
					break;
				case 4:
					cout << "O";
			}
		}
		cout << "|" << endl;
	}
	cout << "-----------------" << endl;
}

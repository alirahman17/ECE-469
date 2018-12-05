#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

  string network, outputfile, test;
  ifstream netfile, testfile;
  ofstream reportfile;

  // IO Setup
  cout << "Enter name of initial neural network file: ";
  getline (cin,network);

  cout << "Enter name of training set file: ";
  getline (cin,test);

  cout << "Enter name of output file: ";
  getline (cin,outputfile);

  netfile.open(network.c_str());
  if(!netfile){                            // error handling for inputfile
    cerr << "ERROR: Unable to open " << network;
    return(-1);
  }

  testfile.open(test.c_str());
  if(!testfile){                           // error handling for testfile
    cerr << "ERROR: Unable to open " << test;
    return(-1);
  }

  reportfile.open(outputfile.c_str());
  if(!reportfile){                             // error handling for outputfile
    cerr << "ERROR: Unable to open " << outputfile;
    return(-1);
  }


  return 0;
}

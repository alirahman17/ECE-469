#include <iostream>
#include <fstream>
#include <string>
#include "neuralNet.hpp"

using namespace std;

int main(){

  string netNeural, outputfile, test;
  ifstream netfile, testfile;
  ofstream reportfile;

  // IO Setup
  cout << "Enter name of trained neural network file: ";
  getline (cin,netNeural);

  cout << "Enter name of test set file: ";
  getline (cin,test);

  cout << "Enter name of results file: ";
  getline (cin,outputfile);

  netfile.open(netNeural.c_str());
  if(!netfile){                            // error handling for inputfile
    cerr << "ERROR: Unable to open " << netNeural;
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

  NeuralNet network;
  network.networkTest(netfile, testfile, reportfile);

  netfile.close();
  testfile.close();
  reportfile.close();

  return 0;
}

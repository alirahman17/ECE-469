#include <iostream>
#include <fstream>
#include <string>
#include "neuralNet.hpp"

using namespace std;

int main(){

  string initneural, outputfile, trainingfile, epochS, learnRateS;
  string::size_type sz;
  ifstream initfile, trainfile;
  ofstream outfile;

  // IO Setup
  cout << "Enter name of initial neural network file: ";
  getline (cin,initneural);

  cout << "Enter name of training set file: ";
  getline (cin,trainingfile);

  cout << "Enter name of output file: ";
  getline (cin,outputfile);

  cout << "Enter value for epoch: ";
  getline (cin,epochS);
  unsigned int epoch = stoul(epochS,nullptr,0);

  cout << "Enter value for learning rate: ";
  getline (cin,learnRateS);
  float learnRate = stof(learnRateS,&sz);

  initfile.open(initneural.c_str());
  if(!initfile){                            // error handling for inputfile
    cerr << "ERROR: Unable to open " << initneural;
    return(-1);
  }

  trainfile.open(trainingfile.c_str());
  if(!trainfile){                           // error handling for inputfile
    cerr << "ERROR: Unable to open " << trainingfile;
    return(-1);
  }

  outfile.open(outputfile.c_str());
  if(!outfile){                             // error handling for outputfile
    cerr << "ERROR: Unable to open " << outputfile;
    return(-1);
  }

  NeuralNet network;
  network.networkTrain(initfile, trainfile, outfile, epoch, learnRate);

  return 0;
}

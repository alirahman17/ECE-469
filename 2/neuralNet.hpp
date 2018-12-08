#ifndef _NEURALNET_HPP
#define _NEURALNET_HPP

#include <list>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class NeuralNet {
  private:
    class Data{
      public:
      vector<double> inputs;
      vector<double> outputs;
    };
    class DataOut{
      public:
        unsigned int a, b, c, d;
        double acc, prec, recall, f1;
    };
    class Node;
    class Edge{
      public:
      double weight;
      Node* prev;
      Node* next;
      unsigned int p[2];
      unsigned int n[2];
    };
    class Node{
      public:
        double insum;
        double activation;
        double delta;
        bool bias;
        vector<Edge *> inEdge;
        vector<Edge *> outEdge;
    };
  public:
    double sigmoid(double val);
    double sigmoidPrime(double val);
    void networkTrain(ifstream &initfile, ifstream &trainfile, ofstream &outfile, unsigned int epoch, float learnRate);
    void networkTest(ifstream &netfile, ifstream &testfile, ofstream &reportfile);
    void readNetFile(ifstream &infile);
    vector<vector<Node *>> nodes1;
    vector<Edge *> edgeList;
};

#endif

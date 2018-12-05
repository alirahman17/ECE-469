#ifndef _NEURALNET_HPP
#define _NEURALNET_HPP

#include <list>

using namespace std;

class NeuralNet {
  public:
    NeuralNet();
    double sigmoid(double val);
    double sigmoidPrime(double val);

  private:

};

#endif

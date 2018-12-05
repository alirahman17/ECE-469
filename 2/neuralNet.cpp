#include "neuralNet.hpp"

using namespace std;

NeuralNet::NeuralNet();

double NeuralNet::sigmoid(double val){
  return 1.0 / (1.0 + exp(-val));
}

double NeuralNet::sigmoidPrime(double val){
  return sigmoid(val) * (1- sigmoid(val));
}

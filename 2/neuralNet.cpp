#include "neuralNet.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

double NeuralNet::sigmoid(double val){
  return 1.0 / (1.0 + exp(-val));
}

double NeuralNet::sigmoidPrime(double val){
  return sigmoid(val) * (1- sigmoid(val));
}

void NeuralNet::networkTrain(ifstream &initfile, ifstream &trainfile, ofstream &outfile, unsigned int epoch, float learnRate){
  readNetFile(initfile);
  unsigned long long numTrain, inputN, outputN;
  double nodeVal;
  vector<Data> trainingSet;
  Node *node;
  Edge *edge;
  double sum;
  // First Line of Training File
  trainfile >> numTrain >> inputN >> outputN;
  for(unsigned int i = 0; i < numTrain; i++){
    NeuralNet::Data tmp;
    for(unsigned int j = 0; j < inputN; j++){
      trainfile >> nodeVal;
      // Input Node
      tmp.inputs.push_back(nodeVal);
    }
    for(unsigned int j = 0; j < outputN; j++){
      trainfile >> nodeVal;
      // Output Node
      tmp.outputs.push_back(nodeVal);
    }
    trainingSet.push_back(tmp);
  }
  for(unsigned int e = 0; e < epoch; e++){
    for(unsigned int i = 0; i < trainingSet.size(); i++){
      // Input Nodes
      for(unsigned int j = 1; j < this->nodes1[0].size(); j++){
        this->nodes1[0][j]->activation = trainingSet[i].inputs[j-1];
      }
      // Hidden/Output layers
      for(unsigned int j = 1; j < this->nodes1.size(); j++){
        for(unsigned int k = 0; k < this->nodes1[j].size(); k++){
          if(this->nodes1[j][k]->bias){
            this->nodes1[j][k]->insum = 0.0;
          } else{
            sum = 0.0;
            for(unsigned int l = 0; l < this->nodes1[j][k]->inEdge.size(); l++){
              sum += this->nodes1[j][k]->inEdge[l]->weight * this->nodes1[j][k]->inEdge[l]->prev->activation;
            }
            this->nodes1[j][k]->insum = sum;
            this->nodes1[j][k]->activation = sigmoid(sum);
          }
        }
      }
      // Output Nodes
      for(unsigned int j = 0; j < this->nodes1[this->nodes1.size() - 1].size(); j++){
        node = this->nodes1[this->nodes1.size() - 1][j];
        node->delta = sigmoidPrime(node->insum) * (trainingSet[i].outputs[j] - node->activation);
      }
      for(unsigned int j = this->nodes1.size() - 2; j > 0; j--){
        for(unsigned int k = 0; k < this->nodes1[j].size(); k++){
          node = this->nodes1[j][k];
          sum = 0.0;
          for(unsigned int l = 0; l < node->outEdge.size(); l++){
            sum += node->outEdge[l]->weight * node->outEdge[l]->next->delta;
          }
          node->delta = sigmoidPrime(node->insum) * sum;
        }
      }
      for(unsigned int j = 0; j < this->edgeList.size(); j++){
        edge = this->edgeList[j];
        edge->weight = edge->weight + (learnRate * edge->prev->activation * edge->next->delta);
      }
    }
  }
  // Output To File
  for(unsigned int i = 0; i < this->nodes1.size(); i++){
    outfile << ((i == this->nodes1.size() - 1) ? this->nodes1[i].size() : this->nodes1[i].size() - 1);
    if(i != this->nodes1.size() - 1) {
        outfile << " ";
    }
  }
  outfile << endl;
  for(unsigned int i = 1; i < this->nodes1.size(); i++){
    for(unsigned int j = 0; j < this->nodes1[i].size(); j++){
      if(!this->nodes1[i][j]->bias){
        for(unsigned int k = 0; k < this->nodes1[i][j]->inEdge.size(); k++){
          outfile << setprecision(3) << fixed << this->nodes1[i][j]->inEdge[k]->weight;
          if(k != this->nodes1[i][j]->inEdge.size() - 1){
            outfile << " ";
          }
        }
        outfile << endl;
      }
    }
  }
}

void NeuralNet::networkTest(ifstream &netfile, ifstream &testfile, ofstream &reportfile){
  readNetFile(netfile);
  unsigned long long count, inputN, outputN;
  double nodeVal, sum;
  vector<Data> testingSet;
  vector<DataOut> testingOut;
  Data tmp;
  DataOut dataPoint;
  testfile >> count >> inputN >> outputN;

  for(unsigned int i = 0; i < count; i++){
    for(unsigned int j = 0; j < inputN; j++) {
        testfile >> nodeVal;
        tmp.inputs.push_back(nodeVal);
    }
    for(unsigned int j = 0; j < outputN; j++) {
        testfile >> nodeVal;
        tmp.outputs.push_back(nodeVal);
    }
    testingSet.push_back(tmp); // push the datapoint into the set
    tmp.inputs.clear();
    tmp.outputs.clear();
  }

  dataPoint.a = dataPoint.b = dataPoint.c = dataPoint.d = 0;
  for(unsigned int i = 0; i < this->nodes1[this->nodes1.size() - 1].size(); i++){
    testingOut.push_back(dataPoint);
  }
  for(unsigned int i = 0; i < testingSet.size(); i++){
    for(unsigned int j = 1; j < this->nodes1[0].size(); j++){
      this->nodes1[0][j]->activation = testingSet[i].inputs[j - 1];
    }
    for(unsigned int j = 1; j < this->nodes1.size(); j++){
      for(unsigned int k = 0; k < this->nodes1[j].size(); k++){
        if(this->nodes1[j][k]->bias){
          this->nodes1[j][k]->insum = 0.0;
        } else{
          sum = 0.0;
          for(unsigned int l = 0; l < this->nodes1[j][k]->inEdge.size(); l++){
            sum += this->nodes1[j][k]->inEdge[l]->weight * this->nodes1[j][k]->inEdge[l]->prev->activation;
          }
          this->nodes1[j][k]->insum = sum;
          this->nodes1[j][k]->activation = sigmoid(sum);
        }
      }
    }
    for(unsigned int j = 0; j < testingOut.size(); j++){
      unsigned int m = round(this->nodes1[this->nodes1.size() - 1][j]->activation);

      if(m == 1 && testingSet[i].outputs[j] == 1){
        testingOut[j].a++;
      }
      if(m == 1 && testingSet[i].outputs[j] == 0){
        testingOut[j].b++;
      }
      if(m == 0 && testingSet[i].outputs[j] == 1){
        testingOut[j].c++;
      }
      if(m == 0 && testingSet[i].outputs[j] == 0){
        testingOut[j].d++;
      }
    }
  }
  reportfile << setprecision(3) << fixed;
  double a, b, c, d, acc, prec, recall, f1;
  for(unsigned int i = 0; i < testingOut.size(); i++){
    a = testingOut[i].a;
    b = testingOut[i].b;
    c = testingOut[i].c;
    d = testingOut[i].d;
    testingOut[i].acc = (a + d) / (a + b + c + d);
    testingOut[i].prec = a / (a + b);
    testingOut[i].recall = a / (a + c);
    testingOut[i].f1 = (2 * testingOut[i].prec * testingOut[i].recall) / (testingOut[i].prec + testingOut[i].recall);

    reportfile << (unsigned int)a << " " << (unsigned int)b << " " << (unsigned int)c << " " << (unsigned int)d << " ";
    reportfile << testingOut[i].acc << " " << testingOut[i].prec << " " << testingOut[i].recall << " " << testingOut[i].f1 << endl;
  }
  a = b = c = d = acc = prec = recall = f1 = 0.0;
  for(unsigned int i = 0; i < testingOut.size(); i++){
    a += testingOut[i].a;
    b += testingOut[i].b;
    c += testingOut[i].c;
    d += testingOut[i].d;
  }
  reportfile << (a + d) / (a + b + c + d) << " " << a / (a + b) << " " << a / (a + c) << " " << ((2 * (a / (a + b)) * (a / (a + c))) / ((a / (a + b)) + (a / (a + c)))) << endl;
  for(unsigned int i = 0; i < testingOut.size(); i++){
    acc += testingOut[i].acc;
    prec += testingOut[i].prec;
    recall += testingOut[i].recall;
  }

  acc = acc / testingOut.size();
  prec = prec / testingOut.size();
  recall = recall / testingOut.size();

  reportfile << acc << " " << prec << " " << recall << " " << ((2 * prec * recall) / (prec + recall)) << endl;
}

void NeuralNet::readNetFile(ifstream &infile){
  string buf, token;
  getline(infile, buf);
  istringstream iss(buf);
  vector<unsigned int> counts;

  while(iss >> token){
    counts.push_back(stoul(token.c_str(),nullptr,0));
  }

  vector<double> weights;
  vector<vector<double>> nodes;
  vector<vector<vector<double>>> layers;

  weights.push_back(1);
  nodes.push_back(weights);
  weights.clear();

  // Input Layer
  for(unsigned int i = 0; i < counts[0]; i++){
    weights.push_back(1);
    nodes.push_back(weights);
    weights.clear();
  }

  layers.push_back(nodes);
  nodes.clear();

  for(unsigned int i = 1; i < counts.size(); i++){
    if(i < counts.size() - 1) {
      weights.push_back(1);
      nodes.push_back(weights);
      weights.clear();
    }
    for(unsigned int j = 0; j < counts[i]; j++){
      getline(infile, buf);
      iss = istringstream(buf);
      while(iss >> token){
        weights.push_back(strtod(token.c_str(), nullptr));
      }
      nodes.push_back(weights);
      weights.clear();
    }
    layers.push_back(nodes);
    nodes.clear();
  }
  // Configure Weights
  Node* node;
  Edge * edge;
  vector<Node *> layerNodes;
  for(unsigned int i = 0; i < layers[0].size(); i++){
    node = new Node;

    if(i){
      node->activation = 0.0;
      node->bias = false;
    } else{
      node->activation = -1.0;
      node->bias = true;
    }
    node->inEdge.push_back(nullptr);
    layerNodes.push_back(node);
  }
  this->nodes1.push_back(layerNodes);
  layerNodes.clear();
  // Hidden Layer
  for(unsigned int i = 1; i < layers.size() - 1; i++){
    for(unsigned int j = 0; j < layers[i].size(); j++){
      node = new Node;
      if(j){
        node->activation = 0.0;
        node->bias = false;
        for(unsigned int k = 0; k < layers[i][j].size(); k++){
          edge = new Edge;
          edge->weight = layers[i][j][k];
          edge->prev = this->nodes1[i-1][k];
          edge->next = node;
          edge->p[0] = i - 1;
          edge->p[1] = k;
          edge->n[0] = i;
          edge->n[1] = j;
          this->edgeList.push_back(edge);
          this->nodes1[i-1][k]->outEdge.push_back(edge);
          node->inEdge.push_back(edge);
        }
      } else{
        node->activation = -1.0;
        node->bias = true;
        node->inEdge.push_back(nullptr);
      }
      layerNodes.push_back(node);
    }
    this->nodes1.push_back(layerNodes);
    layerNodes.clear();
  }
  // Output layer
  for(unsigned int i = 0; i < layers[layers.size()-1].size(); i++){
    node = new Node;
    node->activation = 0.0;
    node->bias = false;
    for(unsigned int j = 0; j < layers[layers.size()-1][i].size(); j++){
      edge = new Edge;
      edge->weight = layers[layers.size() - 1][i][j];
      edge->prev = this->nodes1[layers.size() - 2][j];
      edge->next = node;
      edge->p[0] = layers.size() - 2;
      edge->p[1] = j;
      edge->n[0] = layers.size() - 1;
      edge->n[1] = i;
      this->edgeList.push_back(edge);
      this->nodes1[layers.size() - 2][j]->outEdge.push_back(edge);
      node->inEdge.push_back(edge);
    }

    layerNodes.push_back(node);
  }
  this->nodes1.push_back(layerNodes);
  layerNodes.clear();

}

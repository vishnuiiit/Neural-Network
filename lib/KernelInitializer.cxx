#include "KernelInitializer.h"

#include <time.h>

#include <iostream>
#include <random>
using namespace std;
using namespace Eigen;

MatrixXd Initializers::HeNormal::generate(int lastLayerSize,
                                          int currentLayerSize) {
  static default_random_engine eng(time(0));
  MatrixXd matrix(currentLayerSize, lastLayerSize + 1);
  matrix << VectorXd::Zero(currentLayerSize),
      MatrixXd::Zero(currentLayerSize, lastLayerSize)
          .unaryExpr([lastLayerSize, currentLayerSize](double dummy) {
            normal_distribution<double> dist(0, sqrt(2.0 / (lastLayerSize)));
            return dist(eng);
          });
  return matrix;
}

unique_ptr<KernelInitializer> Initializers::HeNormal::clone() const {
  return make_unique<Initializers::HeNormal>();
}

MatrixXd Initializers::GlorotNormal::generate(int lastLayerSize,
                                              int currentLayerSize) {
  static default_random_engine eng(time(0));
  MatrixXd matrix(currentLayerSize, lastLayerSize + 1);
  matrix << VectorXd::Zero(currentLayerSize),
      MatrixXd::Zero(currentLayerSize, lastLayerSize)
          .unaryExpr([lastLayerSize, currentLayerSize](double dummy) {
            normal_distribution<double> dist(
                0, sqrt(2.0 / (lastLayerSize + currentLayerSize)));
            return dist(eng);
          });
  return matrix;
}

unique_ptr<KernelInitializer> Initializers::GlorotNormal::clone() const {
  return make_unique<Initializers::GlorotNormal>();
}

MatrixXd Initializers::Zero::generate(int lastLayerSize, int currentLayerSize) {
  return MatrixXd::Zero(currentLayerSize, lastLayerSize + 1);
}

unique_ptr<KernelInitializer> Initializers::Zero::clone() const {
  return make_unique<Initializers::Zero>();
}
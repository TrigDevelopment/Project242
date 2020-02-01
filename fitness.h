#pragma once
#include "program.h"

double goal(double x) {
  return exp(x);
}
double getFitness(CRProgram program) {
  double error = 0;
  for (int x = 0; x < 10; ++x) {
    error += abs(goal(x) - proceed(program, x));
  }
  return error * program.size();
}
std::vector<double> getFitnesses(std::vector<Program> const & programs) {
  std::vector<double> fitnesses;
  for (auto const & program : programs) {
    fitnesses.push_back(getFitness(program));
  }
  return fitnesses;
}
double getSum(std::vector<double> fitnesses) {
  double sum = 0;
  for (auto const f : fitnesses) {
    sum += f;
  }
  return sum;
}
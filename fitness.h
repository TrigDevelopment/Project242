double goal(double x) {
  return exp(x);
}
double getFitness(CRProgram program) {
  double error = 0;
  for (int x = 0; x < 10; ++x) {
    error += abs(goal(x) - proceed(program, x));
  }
  return error;
}
std::vector<double> getFitnesses(Programs const & programs) {
  std::vector<double> fitnesses;
  for (auto const & program : programs) {
    fitnesses.push_back(getFitness(program));
  }
  return fitnesses;
}
Program getBest(Programs const & programs) {
  Program minProgram;
  double minFitness = std::numeric_limits<double>::max();
  for (auto program : programs) {
    auto fitness = getFitness(program);
    if (fitness < minFitness) {
      minProgram = program;
      minFitness = fitness;
    }
  }
  return minProgram;
}
double getSum(std::vector<double> fitnesses) {
  double sum = 0;
  for (auto const f : fitnesses) {
    sum += f;
  }
  return sum;
}
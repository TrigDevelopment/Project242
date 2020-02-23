double goal(double x) {
  return exp(x);
}
double getFitness(CRProgram program) {
  double error = 0;
  for (int i = 0; i < 100; ++i) {
    double x = static_cast<double>(rand()) / RAND_MAX * 10;
    //x = i + 1;
    error += abs(goal(x) - proceedDepth(program, 0, x));
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
  Program minProgram = programs[0];
  double minFitness = getFitness(programs[0]);
  for (auto const & program : programs) {
    auto fitness = getFitness(program);
    if (fitness < minFitness) {
      minProgram = program;
      minFitness = fitness;
    }
  }
  return minProgram;
}
Program getBetter(CRProgram left, CRProgram right) {
  return getFitness(left) < getFitness(right) ? left : right;
}
double getSum(std::vector<double> fitnesses) {
  double sum = 0;
  for (auto const f : fitnesses) {
    sum += f;
  }
  return sum;
}
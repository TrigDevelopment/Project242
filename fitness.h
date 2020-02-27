double goal(double x) {
  return exp(x);
}

std::vector<double> getFitnesses(std::vector<Program> const & programs) {
  std::vector<double> fitnesses;
  for (auto const & program : programs) {
    fitnesses.push_back(program.fitness());
  }
  return fitnesses;
}
Program getBest(std::vector<Program> const & programs) {
  Program minProgram = programs[0];
  double minFitness = programs[0].fitness();
  for (auto const & program : programs) {
    auto fitness = program.fitness();
    if (fitness < minFitness) {
      minProgram = program;
      minFitness = fitness;
    }
  }
  return minProgram;
}
Program getBetter(Program const & left, Program const & right) {
  return left.fitness() < right.fitness() ? left : right;
}
double getSum(std::vector<double> fitnesses) {
  double sum = 0;
  for (auto const f : fitnesses) {
    sum += f;
  }
  return sum;
}
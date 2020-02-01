#include "fitness.h"
#include <limits>

const int nPrograms = 100;
std::uniform_int_distribution<std::mt19937::result_type> randProgram(0, nPrograms);
void sift(std::vector<Program> & programs, std::vector<double> const & fitnesses) {
  std::vector<size_t> toKill;
  auto sum = getSum(fitnesses);
  for (size_t i = 0; i < programs.size(); ++i) {
    if (fitnesses[i] / sum < rand() / RAND_MAX) {
      toKill.push_back(i);
    }
  }
  for (size_t i = 0; i < toKill.size(); ++i) {
    programs.erase(programs.begin() + toKill[i]);
  }
}
Program breed(CRProgram A, CRProgram B) {
  return A;
}
void crossover(std::vector<Program> & programs) {
  while (programs.size() < nPrograms) {
    auto first = randProgram(rng);
    auto second = randProgram(rng);
    programs.push_back(breed(programs[first], programs[second]));
  }
}
void growRandom() {
  Program minProgram;
  double minError = std::numeric_limits<double>::max();
  for (int i = 0; i < 400 * 1000; ++i) {
    auto program = grow(24);
    auto error = getFitness(program);
    if (error < minError) {
      minProgram = program;
      minError = error;
    }
  }
  output(minProgram);
  std::cout << minError << std::endl;
  std::cout << mform(minProgram) << std::endl;
}
int main() {
  //output(ramp(10, 6));
  std::vector<Program> programs = ramp(nPrograms, 8);
  for (size_t i = 0; i < 20; ++i) {
    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses);
    crossover(programs);
  }
  system("pause");
  return 0;
}
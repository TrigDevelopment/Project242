#include "output.h"
#include <limits>

const int nPrograms = 20;
RandomInt randProgram(0, nPrograms);
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
  for (int i = 0; i < 4000 * 1000; ++i) {
    auto program = grow(24);
    auto error = getFitness(program);
    if (error < minError) {
      minProgram = program;
      minError = error;
    }
  }
  output(minProgram);
  std::cout << minError << std::endl;
  std::cout << tform(minProgram) << std::endl;
}
void debugProgram() {
  auto pr = Program{ 30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50, 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29 };
  killChildren(pr, 20);
  auto s = tform(pr);
  std::cout << s << std::endl;
}
int main() {
  for (int i = 0; i < 1000; ++i) {
    auto pr = grow(80);
    RandomInt random(0, pr.size() - 1);
    killChildren(pr, random(dev));
  }
  //auto s = tform(Program {2, 2, 2, 1});
  //growRandom();
  //Program pr = { 2, 2, 1 };
  //std::cout << tform(pr) << std::endl;
  //auto programs = ramp(nPrograms, 3);
  //for (auto const & program : programs) {
  //  std::cout << tform(program) << std::endl;
  //}
  //std::vector<Program> programs = ramp(nPrograms, 8);
  //for (size_t i = 0; i < 20; ++i) {
  //  auto fitnesses = getFitnesses(programs);
  //  sift(programs, fitnesses);
  //  crossover(programs);
  //}
  system("pause");
  return 0;
}
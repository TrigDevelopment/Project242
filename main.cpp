#include <random>
#include <vector>
#include <array>
#include <string>
#include <deque>
#include <iostream>

#include "types.h"
#include "debugOperations2.h"
#include "init.h"
#include "program.h"
#include "fitness.h"
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
  auto pr1 = Program{ 30,31,32,33,34,35,36,37,38, 0,0,0,  42,43,44,45,46,47,48,49,50, 0,1,2,3,4,5,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29 };
  auto pr3 = Program{ 31,31,32,33,36,37,38, 0,0,0,  42,43,44, 0,1,2,3,4,5,12,13,14,15,16,17 };
  auto pr4 = Program{ 31,31,32,33,36,37,38, 0,0,0,  0,0,0, 0,1,2,3,4,5 };
  auto pr2 = Program{ 31,31,32,36,37,38, 0,0,0,  0,1,2,3,4,5 };
  auto s2 = tform(pr2);
  std::cout << s2 << std::endl;
  killChildren(pr2, 2);
  auto s = tform(pr2);
  std::cout << s << std::endl;
}
void debugProgram2() {
  auto fullProgram = Program{
    opId("F_0"),
      opId("D_0"), opId("D_1"), opId("D_2"), opId("D_3"), opId("D_4"),
        opId("C_0"), opId("C_1"), opId("C_2"),
        opId("C_3"), opId("C_4"), opId("C_5"),
        opId("C_6"), opId("C_7"), opId("C_8"),
        opId("C_9"), opId("C_10"), opId("C_11"),
        opId("C_12"), opId("C_13"), opId("C_14"),
          opId("A_0"),opId("A_1"),opId("A_2"),opId("A_3"),opId("A_4"),opId("A_5"),
          opId("A_6"),opId("A_7"),opId("A_8"),opId("A_9"),opId("A_10"),opId("A_11"),
          opId("A_12"),opId("A_13"),opId("A_14"),opId("A_15"),opId("A_16"),opId("A_17"),
          opId("A_18"),opId("A_19"),opId("A_20"),opId("A_21"),opId("A_22"),opId("A_23"),
          opId("A_24"),opId("A_25"),opId("A_26"),opId("A_27"),opId("A_28"),opId("A_29"),
  };
  auto fullProgram2 = Program{
    opId("D_0"),
      opId("D_0"), opId("D_1"), opId("D_2"),
        opId("C_0"), opId("C_1"), opId("C_2"),
        opId("C_3"), opId("C_4"), opId("C_5"),
        opId("C_6"), opId("C_7"), opId("C_8"),
          opId("A_0"),opId("A_1"),opId("A_2"),opId("A_3"),opId("A_4"),opId("A_5"),
          opId("A_6"),opId("A_7"),opId("A_8"),opId("A_9"),opId("A_10"),opId("A_11"),
          opId("A_12"),opId("A_13"),opId("A_14"),opId("A_15"),opId("A_16"),opId("A_17"),
  };
  std::cout << tform(fullProgram2) << std::endl;
}
int main() {
  debugProgram2();
  //for (int i = 0; i < 1000; ++i) {
  //  auto pr = grow(80);
  //  RandomInt random(0, pr.size() - 1);
  //  killChildren(pr, random(dev));
  //}
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
#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>

#include "params.h"
#include "types.h"
#include "operations.h"
#include "init.h"
#include "program.h"
#include "fitness.h"
#include "sift.h"
#include "output.h"
#include "scenarios.h"

void crossover(Programs & programs) {
  while (programs.size() < nPrograms) {
    auto first = randBig(dev) % programs.size();
    auto second = randBig(dev) % programs.size();
    size_t toRootI = randBig(dev) % programs[first].size();
    size_t fromRootI = randBig(dev) % programs[second].size();
    auto newProgram = breed(programs[first], programs[second], toRootI, fromRootI, maxSize);
    programs.push_back(newProgram);
  }
}
int rangedRandom(Range const & range) {
  return randBig(dev) % (range.end - range.start) + range.start;
}
void mutate(Programs & programs) {
  size_t programI = rangedRandom(Range{0, static_cast<int>(programs.size())});
  auto program(programs[programI]);
  size_t point = rangedRandom(Range{0, static_cast<int>(program.size())});
  auto operation = program[point];
  auto arity = arities[operation];
  auto newOperation = rangedRandom(arityRanges[arity]);
  program[point] = newOperation;
  programs.push_back(program);
}
void evolution() {
  std::vector<Program> programs = ramp(nPrograms, maxDepth, maxSize);
  for (size_t i = 0; i < nGenerations; ++i) {
    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses);
    crossover(programs);
    for (size_t i = 0; i < nMutationsPerGeneration; ++i) {
      mutate(programs);
    }
  }
  auto best = getBest(programs);
  output(best);
  std::cout << getFitness(best) << std::endl;
}
int main() {
  evolution();
  system("pause");
  return 0;
}
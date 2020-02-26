#include <array>
#include <deque>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <vector>
#include <chrono>
#include <ctime> 
#include <sstream>
#include <unordered_set>

#include "date.h"
#include "types.h"
#include "ops.h"
#include "operations.h"
#include "helpers.h"
#include "init.h"
#include "program.h"
#include "mutate.h"
#include "fitness.h"
#include "sift.h"
#include "output.h"
#include "scenarios.h"

struct DebugParams {
  const size_t nPopulations = 2;
  const size_t nGenerations = 12;
  const size_t nPrograms = 7;
  const size_t nMutationsPerGeneration = 4;
  const size_t maxSize = std::numeric_limits<size_t>::max();
  const size_t maxDepth = 8;
} debugParams;
struct ReleaseParams {
  const size_t nPopulations = 4;
  const size_t nGenerations = 400;
  const size_t nPrograms = 200;
  const size_t nMutationsPerGeneration = 50;
  const size_t maxSize = std::numeric_limits<size_t>::max();
  const size_t maxDepth = 14;
} releaseParams;
void evo() {
  auto params = releaseParams;
  const size_t nPopulations = params.nPopulations;
  const size_t nGenerations = params.nGenerations;
  const size_t nPrograms = params.nPrograms;
  const size_t nMutationsPerGeneration = params.nMutationsPerGeneration;
  const size_t maxSize = params.maxSize;
  const size_t maxDepth = params.maxDepth;
  auto best = evolution(nGenerations, nPrograms, nMutationsPerGeneration, maxSize, maxDepth);
  for (size_t i = 0; i < nPopulations - 1; ++i) {
    best = getBetter(best,
      evolution(nGenerations, nPrograms, nMutationsPerGeneration, maxSize, maxDepth));
  }
  output(best);
}

int main() {
  evo();
  //auto population = ramp(10, 12, std::numeric_limits<size_t>::max());
  //output(population);
  
  system("pause");
  return 0;
}
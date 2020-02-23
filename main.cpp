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

#include "date.h"
#include "types.h"
#include "operations.h"
#include "helpers.h"
#include "init.h"
#include "program.h"
#include "mutate.h"
#include "fitness.h"
#include "sift.h"
#include "output.h"
#include "scenarios.h"

int main() {
  const size_t nPopulations = 4;
  const size_t nGenerations = 40;
  const size_t nPrograms = 20;
  const size_t nMutationsPerGeneration = 4;
  const size_t maxSize = std::numeric_limits<size_t>::max();
  const size_t maxDepth = 8;
  auto best = evolution(nGenerations, nPrograms, nMutationsPerGeneration, maxSize, maxDepth);
  for (size_t i = 0; i < nPopulations; ++i) {
    best = getBetter(best,
      evolution(nGenerations, nPrograms, nMutationsPerGeneration, maxSize, maxDepth));
  }
  output(best);
  system("pause");
  return 0;
}
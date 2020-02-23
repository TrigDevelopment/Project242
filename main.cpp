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
#include "helpers.h"
#include "init.h"
#include "program.h"
#include "mutate.h"
#include "fitness.h"
#include "sift.h"
#include "output.h"
#include "scenarios.h"

int main() {
  const size_t nGenerations = 3;
  const size_t nPrograms = 200;
  const size_t nMutationsPerGeneration = 40;
  const size_t maxSize = std::numeric_limits<size_t>::max();
  const size_t maxDepth = 28;
  evolution(nGenerations, nPrograms, nMutationsPerGeneration, maxSize, maxDepth);
  system("pause");
  return 0;
}
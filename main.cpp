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
#include "program.h"
#include "ops.h"
#include "operations.h"
#include "helpers.h"
#include "init.h"
#include "mutate.h"
#include "fitness.h"
#include "sift.h"

struct DebugParams : public Params {
  size_t nPopulations() const override {
    return 1;
  }
  size_t nGenerations() const override {
    return 6;
  }
  size_t nPrograms() const override {
    return 7;
  }
  size_t freeSpaceForBreed() const override {
    return nPrograms() / 2;
  }
  size_t nMutationsPerGeneration() const override {
    return 4;
  }
  size_t maxSize() const override {
    return std::numeric_limits<size_t>::max();
    //see mutated and crossover method. Don't use until fixed
  }
  size_t maxDepth() const override {
    return 8;
  }
} debugParams;
struct ReleaseParams : public Params {
  size_t nPopulations() const override {
    return 100;
  }
  size_t nGenerations() const override {
    return 2000;
  }
  size_t nPrograms() const override {
    return 200;
  }
  size_t freeSpaceForBreed() const override {
    return static_cast<size_t>(nPrograms() * 0.3);
  }
  size_t nMutationsPerGeneration() const override {
    return 20;
  }
  size_t maxSize() const override {
    return std::numeric_limits<size_t>::max();
  }
  size_t maxDepth() const override {
    return 16;
  }
} releaseParams;

#include "output.h"
#include "scenarios.h"

void evo() {
  auto params = releaseParams;
  std::ofstream file;
  file.open("a_output/table.csv");
  file << "StepI,PopulationI,BestFitness" << std::endl;
  auto best = Program::random(params.maxDepth());
  for (size_t i = 0; i < params.nPopulations(); ++i) {
    auto program = evolution(params, i, file);
    best = getBetter(best, program);
  }
  output(best, params);
  file.close();
}

int main() {
  //auto program = Program::random(5);
  evo();
  //auto population = ramp(10, 12, std::numeric_limits<size_t>::max());
  //output(population);
  
  system("pause");
  return 0;
}
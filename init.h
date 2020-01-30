#pragma once
#include "operations.h"
#include <random>

std::vector<char> grow(int maxDepth) {
  std::vector<char> program;
  int nextLevelLen = 1;
  int depth = 1;

  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> all(0, arities.size() - 1);
  std::uniform_int_distribution<std::mt19937::result_type> terminals(0, maxTerminalId);

  while (nextLevelLen > 0) {
    int levelLen = nextLevelLen;
    nextLevelLen = 0;
    if (depth == maxDepth) {
      for (int i = 0; i < levelLen; ++i) {
        int newOp = terminals(rng);
        program.push_back(newOp);
      }
    }
    else {
      for (int i = 0; i < levelLen; ++i) {
        int newOp = all(rng);
        nextLevelLen += arities[newOp];
        program.push_back(newOp);
      }
    }
    ++depth;
  }
  return program;
}
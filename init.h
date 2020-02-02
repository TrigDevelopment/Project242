#pragma once
#include "debugOperations.h"

std::random_device dev;
std::mt19937 rng(dev());
RandomInt randAll(0, arities.size() - 1);
RandomInt randTerminals(0, maxTerminalId);
Program grow(int maxDepth) {
  Program program;
  int nextLevelLen = 1;
  int depth = 1;

  while (nextLevelLen > 0) {
    int levelLen = nextLevelLen;
    nextLevelLen = 0;
    if (depth == maxDepth) {
      for (int i = 0; i < levelLen; ++i) {
        int newOp = randTerminals(rng);
        program.push_back(newOp);
      }
    }
    else {
      for (int i = 0; i < levelLen; ++i) {
        int newOp = randAll(rng);
        nextLevelLen += arities[newOp];
        program.push_back(newOp);
      }
    }
    ++depth;
  }
  return program;
}
std::vector<Program> ramp(int nPrograms, int maxDepth) {
  std::vector<Program> programs;
  for (int i = 0; i < nPrograms; ++i) {
    programs.push_back(grow(maxDepth));
  }
  return programs;
}
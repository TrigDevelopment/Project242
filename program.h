#pragma once
#include "init.h"
#include <deque>

double proceed(CRProgram program, double x) {
  std::deque<double> deq;
  for (auto it = program.rbegin(); it != program.rend(); ++it) {
    auto operationId = *it;
    std::vector<double> args;
    if (arities[operationId] == 1) {
      args.push_back(deq.front());
      deq.pop_front();
    }
    else if (arities[operationId] == 2) {
      args.push_back(deq.front());
      deq.pop_front();
      args.push_back(deq.front());
      deq.pop_front();
      std::reverse(args.begin(), args.end());
    }
    deq.push_back(proceed(operationId, args, x));
  }
  return deq.front();
}
std::vector<size_t> getLevelSizes(CRProgram program) {
  std::vector<size_t> sizes;
  sizes.push_back(1);
  size_t current = 1;
  size_t next = 0;
  //to prevent adding 0-sized last level, last operation in program is not proceeded (see program.size() - 1 in loop condition)
  for (size_t i = 0; i < program.size() - 1; ++i) {
    next += arities[program[i]];
    --current;
    if (current == 0) {
      current = next;
      sizes.push_back(next);
      next = 0;
    }
  }
  return sizes;
}
std::vector<size_t> getLevelStarts(CRProgram program) {
  std::vector<size_t> starts;
  starts.push_back(0);
  auto const sizes = getLevelSizes(program);
  for (auto const & size : sizes) {
    auto last = starts[starts.size() - 1];
    starts.push_back(last + size);
  }
  starts.pop_back();
  return starts;
}
void killChildren(Program & program, size_t rootI) {
  auto levels = getLevelStarts(program);
  levels.push_back(program.size());
  size_t levelI = 0;
  while (rootI >= levels[levelI + 1]) {
    ++levelI;
  }

  std::vector<size_t> toKill;
  size_t left = rootI;
  size_t right = rootI + 1;
  while (levelI + 1 < levels.size() - 1) {
    ++levelI;
    auto prevLeft = left;
    auto prevRight = right;
    left = levels[levelI];
    for (auto i = levels[levelI - 1]; i < prevLeft; ++i) {
      left += arities[program[i]];
    }
    right = left;
    for (auto i = prevLeft; i < prevRight; ++i) {
      right += arities[program[i]];
    }
    toKill.push_back(left);
    toKill.push_back(right);
  }
  for (int i = toKill.size() - 2; i >= 0; i -= 2) {
    program.erase(program.begin() + toKill[i], program.begin() + toKill[i + 1]);
  }
}
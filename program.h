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
void output(CRProgram program) {
  for (char id : program) {
    std::cout << name(id) << ' ';
  }
  std::cout << std::endl;
}
void output(std::vector<Program> programs) {
  for (auto const & program : programs) {
    output(program);
  }
}
std::string mform(CRProgram program) {
  std::deque<std::string> deq;
  for (auto it = program.rbegin(); it != program.rend(); ++it) {
    auto operationId = *it;
    std::vector<std::string> args;
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
    std::string next;
    switch (operationId) {
      case 0: 
        next = "1";
        break;
      case 1: 
        next = "x";
        break;
      case 2:
        next = "sin " + args[0];
        break;
      case 3:
        next = "(" + args[0] + "+" + args[1] + ")";
        break;
      case 4:
        next = "(" + args[0] + "*" + args[1] + ")";
        break;
    }
    deq.push_back(next);
  }
  return deq.front();
}
std::string tform(CRProgram program) {
  std::string str;
  //auto lefts = getLevelStarts(program);
  std::vector<int> stack;
  stack.push_back(arities[program[0]]);
  //while ()
  return str;
}
#pragma once
#include "init.h"
using Program = std::vector<char> const &;
double proceed(Program program, double x) {
  
}
void output(Program program) {
  for (char id : program) {
    std::cout << name(id) << ' ';
  }
  std::cout << std::endl;
}
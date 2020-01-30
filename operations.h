#pragma once
#include <vector>
#include <iostream>
#include <string>

int maxTerminalId = 1;
std::vector<int> arities = { 0, 0, 1, 2, 2 };
double proceed(int id, std::vector<double> const & args, double x) noexcept {
  switch (id) {
  case 0: return 1;
  case 1: return x;
  case 2: return sin(args[0]);
  case 3: return args[0] + args[1];
  case 4: return args[0] * args[1];
  default: return 0;
  }
}
std::string name(int id) {
  switch (id) {
  case 0: return "1";
  case 1: return "x";
  case 2: return "sin";
  case 3: return "+";
  case 4: return "*";
  default: return "Q";
  }
}
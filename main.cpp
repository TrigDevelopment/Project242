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
  //breedingDepth();
  //breedingDepth();
  //std::cout << rangedRandom({0, 100}) << std::endl;
  growing();
  //evolution();
  //mutation();
  system("pause");
  return 0;
}
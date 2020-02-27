std::vector<Id> grow(size_t maxDepth);
std::vector<Id> full(size_t depth);
std::vector<Id> getRandomProgram(size_t maxDepth) {
  auto depth = rangedRandom({ 1, static_cast<int>(maxDepth + 1)});
  if (rangedRandom({ 0, 2 }) == 0) {
    return grow(depth);
  }
  else {
    return full(depth);
  }
}
std::vector<Id> grow(size_t maxDepth) {
  if (maxDepth == 1) {
    return std::vector<Id>{ getRandTerminalId() };
  }
  else {
    Id id = getRandOpId();
    std::vector<Id> newProgram{ id };
    auto arity = operations[newProgram[0]].arity;
    for (size_t i = 0; i < arity; ++i) {
      auto branch = grow(maxDepth - 1);
      newProgram.insert(newProgram.end(), branch.begin(), branch.end());
    }
    return newProgram;
  }
}
std::vector<Id> full(size_t depth) {
  if (depth == 1) {
    return std::vector<Id>{ getRandTerminalId() };
  }
  else {
    Id id = getRandNonTerminalId();
    std::vector<Id> newProgram{ id };
    auto arity = operations[newProgram[0]].arity;
    for (size_t i = 0; i < arity; ++i) {
      auto branch = full(depth - 1);
      newProgram.insert(newProgram.end(), branch.begin(), branch.end());
    }
    return newProgram;
  }
}

std::vector<Program> ramp(size_t nPrograms, size_t maxDepth, size_t maxSize) {
  std::vector<Program> programs;
  while (programs.size() < nPrograms) {
    auto newProgram = getRandomProgram(maxDepth);
    if (newProgram.size() <= maxSize) {
      programs.push_back(newProgram);
    }
  }
  return programs;
}
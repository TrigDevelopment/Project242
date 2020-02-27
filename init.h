Program_ grow(size_t maxDepth);
Program_ full(size_t depth);
Program_ getRandomProgram(size_t maxDepth) {
  auto depth = rangedRandom({ 1, static_cast<int>(maxDepth + 1)});
  if (rangedRandom({ 0, 2 }) == 0) {
    return grow(depth);
  }
  else {
    return full(depth);
  }
}
Program_ grow(size_t maxDepth) {
  if (maxDepth == 1) {
    return Program_{ getRandTerminalId() };
  }
  else {
    Id id = getRandOpId();
    Program_ newProgram{ id };
    auto arity = getArity(newProgram, 0);
    for (size_t i = 0; i < arity; ++i) {
      auto branch = grow(maxDepth - 1);
      newProgram.insert(newProgram.end(), branch.begin(), branch.end());
    }
    return newProgram;
  }
}
Program_ full(size_t depth) {
  if (depth == 1) {
    return Program_{ getRandTerminalId() };
  }
  else {
    Id id = getRandNonTerminalId();
    Program_ newProgram{ id };
    auto arity = getArity(newProgram, 0);
    for (size_t i = 0; i < arity; ++i) {
      auto branch = grow(depth - 1);
      newProgram.insert(newProgram.end(), branch.begin(), branch.end());
    }
    return newProgram;
  }
}

Programs ramp(size_t nPrograms, size_t maxDepth, size_t maxSize) {
  Programs programs;
  while (programs.size() < nPrograms) {
    auto newProgram = getRandomProgram(maxDepth);
    if (newProgram.size() <= maxSize) {
      programs.push_back(newProgram);
    }
  }
  return programs;
}
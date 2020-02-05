Program growBreadth(int maxDepth) {
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
Program grow(size_t maxDepth) {
  if (maxDepth == 1) {
    return Program{getRandTerminalId()};
  }
  else {
    Id id = getRandOpId();
    Program newProgram{ id };
    auto arity = getArity(newProgram, 0);
    for (size_t i = 0; i < arity; ++i) {
      auto branch = grow(maxDepth - 1);
      newProgram.insert(newProgram.end(), branch.begin(), branch.end());
    }
    return newProgram;
  }
}
Programs rampDepth(size_t nPrograms, size_t maxDepth, size_t maxSize) {
  Programs programs;
  while (programs.size() < nPrograms) {
    auto newProgram = grow(maxDepth);
    if (newProgram.size() <= maxSize) {
      programs.push_back(newProgram);
    }
  }
  return programs;
}
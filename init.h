Program grow(size_t maxDepth);
Program getRandomProgram(size_t maxDepth) {
  return grow(maxDepth);
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
Programs ramp(size_t nPrograms, size_t maxDepth, size_t maxSize) {
  Programs programs;
  while (programs.size() < nPrograms) {
    auto newProgram = grow(maxDepth);
    if (newProgram.size() <= maxSize) {
      programs.push_back(newProgram);
    }
  }
  return programs;
}
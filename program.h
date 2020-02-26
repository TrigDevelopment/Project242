double proceed(CRProgram program, Input const & x) {
  std::vector<double> memory(10, 0);
  return proceed(program, 0, now(), x, memory);
}
size_t getBranchLen(CRProgram program, size_t startI) {
  size_t len = 1;
  size_t toProceed = getArity(program, startI);
  while (toProceed > 0) {
    toProceed += getArity(program, startI + len);
    --toProceed;
    ++len;
  }
  return len;
}
void eraseBranch(Program & program, size_t i) {
  program.erase(program.begin() + i,
    program.begin() + i + getBranchLen(program, i));
}
Program breed(CRProgram from, CRProgram to, size_t fromRootI, size_t toRootI) {
  auto newProgram = to;
  eraseBranch(newProgram, toRootI);
  newProgram.insert(newProgram.begin() + toRootI,
    from.begin() + fromRootI, 
    from.begin() + fromRootI + getBranchLen(from, fromRootI));
  return newProgram;
}
bool valid(CRProgram program, size_t maxSize, size_t maxDepth) {
  return program.size() <= maxSize && getBranchLen(program, 0) <= maxDepth;
}
void crossover(Programs & programs, size_t nPrograms, size_t maxSize, size_t maxDepth) {
  while (programs.size() < nPrograms) {
    auto from = programs[randBig(rng) % programs.size()];
    auto to = programs[randBig(rng) % programs.size()];
    size_t fromRootI = randBig(rng) % from.size();
    size_t toRootI = randBig(rng) % to.size();
    auto newProgram = breed(from, to, fromRootI, toRootI);
    if (valid(newProgram, maxSize, maxDepth)) {
      programs.push_back(newProgram);
    }
    else {
      //programs.push_back(from);
    }
  }
}

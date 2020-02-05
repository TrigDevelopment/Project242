void mutate(Programs & programs) {
  size_t programI = rangedRandom(Range{ 0, static_cast<int>(programs.size()) });
  auto program(programs[programI]);
  size_t point = rangedRandom(Range{ 0, static_cast<int>(program.size()) });
  auto operation = program[point];
  auto arity = arities[operation];
  auto newOperation = rangedRandom(arityRanges[arity]);
  program[point] = newOperation;
  programs.push_back(program);
}
size_t getBranchLenDepth(CRProgram program, size_t startI) {
  size_t len = 1;
  size_t toProceed = arities[program[startI]];
  while (toProceed > 0) {
    toProceed += getArity(program, startI + len);
    --toProceed;
    ++len;
  }
  return len;
}
Program breedDepth(CRProgram from, CRProgram to, size_t fromRootI, size_t toRootI) {
  auto newProgram = to;
  newProgram.erase(newProgram.begin() + toRootI, 
    newProgram.begin() + toRootI + getBranchLenDepth(to, toRootI));
  newProgram.insert(newProgram.begin() + toRootI,
    from.begin() + fromRootI, 
    from.begin() + fromRootI + getBranchLenDepth(from, fromRootI));
  return newProgram;
}
void crossoverDepth(Programs & programs) {
  while (programs.size() < nPrograms) {
    auto from = programs[randBig(rng) % programs.size()];
    auto to = programs[randBig(rng) % programs.size()];
    size_t fromRootI = randBig(rng) % from.size();
    size_t toRootI = randBig(rng) % to.size();
    auto newProgram = breedDepth(from, to, fromRootI, toRootI);
    if (newProgram.size() <= maxSize && getBranchLenDepth(newProgram, 0) <= maxDepth) {
      programs.push_back(newProgram);
    }
  }
}
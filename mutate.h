Program_ getPointMutated(CRProgram program);
Program_ getSubtreeMutated(CRProgram program, size_t maxSize, size_t maxDepth);
void mutate(Programs & programs, size_t maxSize, size_t maxDepth) {
  size_t programI = rangedRandom(Range{ 0, static_cast<int>(programs.size()) });
  auto const & newProgram = getSubtreeMutated(programs[programI], maxSize, maxDepth);
  programs.push_back(newProgram);
}
Program_ getPointMutated(CRProgram program) {
  auto newProgram(program);
  auto point = getRandomNodeI(newProgram);
  auto arity = getArity(program, point);
  auto newOperation = rangedRandom(arityRanges[arity]);
  newProgram[point] = newOperation;
  return newProgram;
}
Program_ getSubtreeMutated(CRProgram program, size_t maxSize, size_t maxDepth) {
  while (true) {
    auto newBranch = getRandomProgram(maxDepth);
    auto newProgram = program;
    auto point = getRandomNodeI(newProgram);
    eraseBranch(newProgram, point);
    newProgram.insert(newProgram.begin() + point,
      newBranch.begin(),
      newBranch.begin() + getBranchLen(newBranch, 0));
    if (valid(newProgram, maxSize, maxDepth)) {
      return newProgram;
    }
  }
}
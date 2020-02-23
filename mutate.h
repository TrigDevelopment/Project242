Program getPointMutated(CRProgram program);
Program getSubtreeMutated(CRProgram program);
void mutate(Programs & programs) {
  size_t programI = rangedRandom(Range{ 0, static_cast<int>(programs.size()) });
  auto const & newProgram = getSubtreeMutated(programs[programI]);
  programs.push_back(newProgram);
}
Program getPointMutated(CRProgram program) {
  auto newProgram(program);
  auto point = getRandomNodeI(newProgram);
  auto arity = getArity(program, point);
  auto newOperation = rangedRandom(arityRanges[arity]);
  newProgram[point] = newOperation;
  return newProgram;
}
Program getSubtreeMutated(CRProgram program) {
  while (true) {
    auto newBranch = getRandomProgram(maxDepth);
    auto newProgram = program;
    auto point = getRandomNodeI(newProgram);
    eraseBranch(newProgram, point);
    newProgram.insert(newProgram.begin() + point,
      newBranch.begin(),
      newBranch.begin() + getBranchLen(newBranch, 0));
    if (valid(newProgram)) {
      return newProgram;
    }
  }
}
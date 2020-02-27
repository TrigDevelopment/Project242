void mutate(std::vector<Program> & programs, size_t maxSize, size_t maxDepth) {
  size_t programI = rangedRandom(Range{ 0, static_cast<int>(programs.size()) });
  auto const & newProgram = programs[programI].getSubtreeMutated(maxSize, maxDepth);
  programs.push_back(newProgram);
}
/*
Program getPointMutated(Program const & program) {
  auto newProgram(program);
  auto point = getRandomNodeI(newProgram);
  auto arity = getArity(program, point);
  auto newOperation = rangedRandom(arityRanges[arity]);
  newProgram[point] = newOperation;
  return newProgram;
}
*/

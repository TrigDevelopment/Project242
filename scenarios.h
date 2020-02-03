void growRandom() {
  Program minProgram;
  double minError = std::numeric_limits<double>::max();
  for (int i = 0; i < 4000 * 1000; ++i) {
    auto program = grow(24);
    auto error = getFitness(program);
    if (error < minError) {
      minProgram = program;
      minError = error;
    }
  }
  output(minProgram);
  std::cout << minError << std::endl;
  std::cout << tform(minProgram) << std::endl;
}
void breeding() {
  while (true) {
    auto to = grow(maxDepth);
    auto from = grow(maxDepth);
    if (to.size() <= maxSize && from.size() <= maxSize) {
      size_t toRootI = randBig(dev) % to.size();
      size_t fromRootI = randBig(dev) % from.size();
      tform(breed(to, from, toRootI, fromRootI, maxSize));
    }
  }
}
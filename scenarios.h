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
void growRandomBreadth() {
  Program minProgram;
  double minError = std::numeric_limits<double>::max();
  for (int i = 0; i < 4000 * 1000; ++i) {
    auto program = growBreadth(24);
    auto error = getFitness(program);
    if (error < minError) {
      minProgram = program;
      minError = error;
    }
  }
  output(minProgram);
  std::cout << minError << std::endl;
  std::cout << tformBreadth(minProgram) << std::endl;
}
void breedingBreadth() {
  while (true) {
    auto to = growBreadth(maxDepth);
    auto from = growBreadth(maxDepth);
    if (to.size() <= maxSize && from.size() <= maxSize) {
      size_t toRootI = randBig(dev) % to.size();
      size_t fromRootI = randBig(dev) % from.size();
      tformBreadth(breedBreadth(to, from, toRootI, fromRootI, maxSize));
    }
  }
}
void breedingDepth() {
  while (true) {
    auto from = growDepth(maxDepth);
    auto to = growDepth(maxDepth);
    size_t fromRootI = randBig(dev) % from.size();
    size_t toRootI = randBig(dev) % to.size();
    output(from);
    output(to);
    auto child = breedDepth(from, to, fromRootI, toRootI);
    output(child);
    std::cout << fromRootI << " " << toRootI << std::endl;
    system("pause");
    //tformDepth(child, 0, 0);
  }
}
void evolutionBreadth() {
  std::vector<Program> programs = rampDepth(nPrograms, maxDepth, maxSize);
  for (size_t i = 0; i < nGenerations; ++i) {
    if (i % 100 == 0 && i > 0) {
      std::cout << "Generation " + std::to_string(i) << std::endl;
    }
    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses);
    crossoverBreadth(programs);
    for (size_t i = 0; i < nMutationsPerGeneration; ++i) {
      mutate(programs);
    }
  }
  auto best = getBest(programs);
  output(best);
  std::cout << getFitness(best) << std::endl;
}
void evolutionDepth() {
  std::vector<Program> programs = rampDepth(nPrograms, maxDepth, maxSize);
  for (size_t i = 0; i < nGenerations; ++i) {
    if (i % 100 == 0 && i > 0) {
      std::cout << "Generation " + std::to_string(i) << std::endl;
    }
    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses);
    crossoverDepth(programs);
    for (size_t i = 0; i < nMutationsPerGeneration; ++i) {
      mutate(programs);
    }
  }
  auto best = getBest(programs);
  output(best);
  std::cout << getFitness(best) << std::endl;
}
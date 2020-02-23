void growing() {
  Program minProgram;
  double minFitness = 1000 * 1000;
  for (size_t i = 0; i < nPrograms; ++i) {
    auto newProgram = getRandomProgram(maxDepth);
    auto newFitness = getFitness(newProgram);
    if (newFitness < minFitness) {
      minFitness = newFitness;
      minProgram = newProgram;
    }
  }
  output(minProgram);
}
void breeding() {
  while (true) {
    auto from = grow(maxDepth);
    auto to = grow(maxDepth);
    size_t fromRootI = randBig(rng) % from.size();
    size_t toRootI = randBig(rng) % to.size();
    output(from);
    output(to);
    auto child = breed(from, to, fromRootI, toRootI);
    output(child);
    std::cout << fromRootI << " " << toRootI << std::endl;
    system("pause");
  }
}
void evolution() {
  std::vector<Program> programs = rampDepth(nPrograms, maxDepth, maxSize);
  for (size_t i = 0; i < nGenerations; ++i) {
    if (i % 1000 == 0 && i > 0) {
      std::cout << "Generation " + std::to_string(i) << std::endl;
      auto best = getBest(programs);
      output(best);
      std::cout << getFitness(best) << std::endl;
    }
    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses);
    crossover(programs);
    for (size_t i = 0; i < nMutationsPerGeneration; ++i) {
      mutate(programs);
    }
  }
  output(getBest(programs));
}
void mutation() {
  while (true) {
    auto program = getRandomProgram(4);
    output(program, true);
    auto mutatedProgram = getPointMutated(program);
    output(mutatedProgram, true);
    system("pause");
  }
}
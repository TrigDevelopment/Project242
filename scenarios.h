void growing(size_t nPrograms, size_t maxDepth) {
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
void breeding(size_t maxDepth) {
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
Program evolution(size_t nGenerations, size_t nPrograms, size_t nMutationsPerGeneration,
  size_t maxSize, size_t maxDepth) {
  std::vector<Program> programs = ramp(nPrograms, maxDepth, maxSize);
  for (size_t i = 0; i < nGenerations; ++i) {
    if (i % 100000 == 0 && i > 0) {
      //std::cout << "Generation " << i << std::endl;
      auto best = getBest(programs);
      //output(best);
      //std::cout << getFitness(best) << std::endl;
      //myfile << name << "," << i << "," << getFitness(best) << "," << mform(best, 0) << std::endl;
    }
    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses);
    crossover(programs, nPrograms, maxSize, maxDepth);
    for (size_t i = 0; i < nMutationsPerGeneration; ++i) {
      mutate(programs, maxSize, maxDepth);
    }
  }
  return getBest(programs);
  //output(getBest(programs));
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
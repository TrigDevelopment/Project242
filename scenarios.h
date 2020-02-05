void breeding() {
  while (true) {
    auto from = grow(maxDepth);
    auto to = grow(maxDepth);
    size_t fromRootI = randBig(rng) % from.size();
    size_t toRootI = randBig(rng) % to.size();
    output(from);
    output(to);
    auto child = breedDepth(from, to, fromRootI, toRootI);
    output(child);
    std::cout << fromRootI << " " << toRootI << std::endl;
    system("pause");
  }
}
void evolution() {
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
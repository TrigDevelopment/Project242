void growing(size_t nPrograms, size_t maxDepth) {
  Program_ minProgram;
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
void toTable(Programs const & programs, size_t populationI, size_t stepI, 
  std::ofstream & file) {
  auto best = getBest(programs);
  file << stepI << "," << populationI << "," << getFitness(best) << std::endl;
}
void outputTimes(Programs const & programs, size_t stepI, std::ofstream & file) {
  for (size_t i = 0; i < programs.size(); ++i) {
    for (int j = 0; j < 10; ++j) {
      double x = j + 1;
      auto startTime = now();
      double value = proceed(programs[i], x);
      MicroSeconds timeElapsed = std::chrono::duration_cast<MicroSeconds>(now() - startTime);
      file << timeElapsed.count() << "," << value << std::endl;
    }
  }
}
Program_ evolution(Params const & params, size_t populationI, std::ofstream & file) {
  std::vector<Program_> programs = ramp(params.nPrograms(), params.maxDepth(), params.maxSize());
  std::ofstream timesFile;
  timesFile.open("a_output/timesFile.csv");
  timesFile << "Time(us),Value" << std::endl;

  for (size_t i = 0; i < params.nGenerations(); ++i) {
    outputTimes(programs, i, timesFile);
    toTable(programs, populationI, i, file);

    auto fitnesses = getFitnesses(programs);
    sift(programs, fitnesses, params.nPrograms() - params.freeSpaceForBreed());
    crossover(programs, params.nPrograms(), params.maxSize(), params.maxDepth());
    for (size_t i = 0; i < params.nMutationsPerGeneration(); ++i) {
      mutate(programs, params.maxSize(), params.maxDepth());
    }
  }

  timesFile.close();
  toTable(programs, populationI, params.nGenerations(), file);
  return getBest(programs);
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
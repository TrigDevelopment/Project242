void tournament(std::vector<Program> & programs, size_t nProgramsToKeep);
std::vector<size_t> selectForTournament(size_t nPrograms, size_t nProgramsToSelect);

void sift(std::vector<Program> & programs, size_t nProgramsToKeep) {
  //best(programs, fitnesses);
  tournament(programs, nProgramsToKeep);
}
void tournament(std::vector<Program> & programs, size_t nProgramsToKeep) {
  size_t nProgramsToSelect = programs.size() - nProgramsToKeep + 1;
  auto selectedIndexes = selectForTournament(programs.size(), nProgramsToSelect);

  auto minFitness = std::numeric_limits<double>::max();
  size_t minI = 0;
  for (auto i : selectedIndexes) {
    auto fitness = programs[i].fitness();
    if (fitness < minFitness) {
      minI = i;
      minFitness = fitness;
    }
  }
  
  for (auto it = selectedIndexes.rbegin(); it != selectedIndexes.rend(); ++it) {
    if (*it != minI) {
      programs.erase(programs.begin() + *it);
    }
  }
}
/* Return sorted vector of indexes */
std::vector<size_t> selectForTournament(size_t nPrograms, size_t nProgramsToSelect) {
  std::unordered_set<int> numbers;
  while (numbers.size() < nProgramsToSelect)
  {
    numbers.insert(rangedRandom({0, static_cast<int>(nPrograms)}));
  }
  std::vector<size_t> vec(numbers.begin(), numbers.end());
  std::sort(vec.begin(), vec.end());
  return vec;
}
void best(std::vector<Program> & programs) 
{
  std::vector<std::pair<size_t, double>> pairs;
  for (size_t i = 0; i < programs.size(); ++i) {
    pairs.push_back(std::make_pair(i, programs[i].fitness()));
  }
  std::sort(pairs.begin(), pairs.end(),
    [](std::pair<size_t, double> const & a, std::pair<size_t, double> const & b) {
    return a.second > b.second;
  });
  auto size = pairs.size();
  while (pairs.size() > size / 2) {
    pairs.pop_back();
  }
  std::vector<size_t> indexes;
  for (auto const & pair : pairs) {
    indexes.push_back(pair.first);
  }
  std::sort(indexes.rbegin(), indexes.rend());
  for (auto const i : indexes) {
    programs.erase(programs.begin() + i);
  }
}
/*
void roulette(std::vector<Program> & programs) {
  std::vector<size_t> toKill;
  auto sum = getSum(fitnesses);
  for (size_t i = 0; i < programs.size(); ++i) {
    //output(programs[i]);
    //std::cout << fitnesses[i] / sum << std::endl;
    //std::cout << std::endl;
    if (fitnesses[i] / sum < static_cast<double>(rand()) / RAND_MAX) {
      toKill.push_back(i);
    }
  }
  if (toKill.size() < programs.size()) {
    for (int i = toKill.size() - 1; i >= 0; --i) {
      programs.erase(programs.begin() + toKill[i]);
    }
  }
}
*/
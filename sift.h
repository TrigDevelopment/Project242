void tournament(Programs & programs, std::vector<double> const & fitnesses);
void sift(Programs & programs, std::vector<double> const & fitnesses) {
  best(programs, fitnesses);
  //tournament(programs, fitnesses);
}
void tournament(Programs & programs, std::vector<double> const & fitnesses) {
  auto selectedIndexes = selectForTournament(programs);

  auto minFitness = std::numeric_limits<double>::max();
  size_t minI = 0;
  for (auto i : selectedIndexes) {
    if (fitnesses[i] < minFitness) {
      minI = i;
      minFitness = fitnesses[i];
    }
  }
  
}
/* Return sorted vector of indexes */
std::vector<size_t> selectForTournament(Programs const & programs) {
  std::unordered_set<int> numbers;
  while (numbers.size() < 40)
  {
    numbers.insert(rangedRandom({0, programs.size()}));
  }
  std::vector<size_t> vec(numbers.begin(), numbers.end());
  std::sort(vec.begin(), vec.end());
  return vec;
}
void best(Programs & programs, std::vector<double> const & fitnesses) {
  std::vector<std::pair<size_t, double>> pairs;
  for (size_t i = 0; i < fitnesses.size(); ++i) {
    pairs.push_back(std::make_pair(i, fitnesses[i]));
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
void roulette(Programs & programs, std::vector<double> const & fitnesses) {
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
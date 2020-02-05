double proceedBreadth(CRProgram program, double x) {
  std::vector<double> deq(program.size());
  auto argI = program.size();
  for (int i = program.size() - 1; i >= 0; --i) {
    auto const opId = program[i];
    auto const arity = arities[opId];
    argI -= arity;
    deq[i] = proceedBreadth(opId, deq, argI, x);
  }
  return deq[0];
}
Indexes getLevelSizesBreadth(CRProgram program) {
  std::vector<size_t> sizes;
  sizes.push_back(1);
  size_t current = 1;
  size_t next = 0;
  //to prevent adding 0-sized last level, last operation in program is not proceeded (see program.size() - 1 in loop condition)
  for (size_t i = 0; i < program.size() - 1; ++i) {
    next += arities[program[i]];
    --current;
    if (current == 0) {
      current = next;
      sizes.push_back(next);
      next = 0;
    }
  }
  return sizes;
}
Indexes getLevelStartsBreadth(CRProgram program) {
  auto const sizes = getLevelSizesBreadth(program);
  std::vector<size_t> starts;
  starts.reserve(sizes.size() + 1);
  starts.push_back(0);
  for (auto const & size : sizes) {
    auto last = starts[starts.size() - 1];
    starts.push_back(last + size);
  }
  starts.pop_back();
  return starts;
}
Indexes getLevelStopsBreadth(CRProgram program) {
  auto stops = getLevelStartsBreadth(program);
  stops.push_back(program.size());
  return stops;
}
size_t getLevelIBreadth(size_t i, std::vector<size_t> const & levelStops) {
  size_t levelI = 0;
  while (i >= levelStops[levelI + 1]) {
    ++levelI;
  }
  return levelI;
}
std::vector<size_t> markChildrenBreadth(CRProgram program, size_t rootI) {
  auto stops = getLevelStopsBreadth(program);
  auto levelI = getLevelIBreadth(rootI, stops);
  std::vector<size_t> marked;
  size_t left = rootI;
  size_t right = rootI + 1;
  while (levelI + 1 < stops.size() - 1) {
    ++levelI;
    auto prevLeft = left;
    auto prevRight = right;
    left = stops[levelI];
    for (auto i = stops[levelI - 1]; i < prevLeft; ++i) {
      left += arities[program[i]];
    }
    right = left;
    for (auto i = prevLeft; i < prevRight; ++i) {
      right += arities[program[i]];
    }
    marked.push_back(left);
    marked.push_back(right);
  }
  return marked;
}
void killChildrenBreadth(Program & program, size_t rootI) {
  std::vector<size_t> toKill = markChildrenBreadth(program, rootI);
  for (int i = toKill.size() - 2; i >= 0; i -= 2) {
    program.erase(program.begin() + toKill[i], program.begin() + toKill[i + 1]);
  }
}
Program breedBreadth(CRProgram to, CRProgram from, size_t toRootI, size_t fromRootI, size_t maxSize) {
  auto newProgram(to);
  killChildrenBreadth(newProgram, toRootI);
  newProgram[toRootI] = getTerminal(); // to make newProgram valid tree after killing children
  auto branchIntervals = markChildrenBreadth(from, fromRootI);
  auto levelStarts = getLevelStartsBreadth(newProgram);
  Indexes insertionPoints;
  auto point = toRootI;
  auto levelI = getLevelIBreadth(toRootI, getLevelStopsBreadth(newProgram));
  for (size_t intervalI = 0; intervalI < branchIntervals.size(); intervalI += 2) {
    ++levelI;
    if (levelI < levelStarts.size()) {
      auto prevPoint = point;
      point = levelStarts[levelI];
      for (size_t i = levelStarts[levelI - 1]; i < prevPoint; ++i) {
        point += arities[newProgram[i]];
      }
      insertionPoints.push_back(point);
    }
    else {
      insertionPoints.push_back(newProgram.size());
    }
  }
  newProgram[toRootI] = from[fromRootI];
  for (int i = insertionPoints.size() - 1; i >= 0; --i){
    newProgram.insert(newProgram.begin() + insertionPoints[i],
      from.begin() + branchIntervals[i * 2], 
      from.begin() + branchIntervals[i * 2 + 1]);
  }
  if (newProgram.size() > maxSize || getLevelSizesBreadth(newProgram).size() > maxDepth) {
    return from;
  }
  else {
    return newProgram;
  }
}
void crossoverBreadth(Programs & programs) {
  while (programs.size() < nPrograms) {
    auto first = randBig(dev) % programs.size();
    auto second = randBig(dev) % programs.size();
    size_t toRootI = randBig(dev) % programs[first].size();
    size_t fromRootI = randBig(dev) % programs[second].size();
    auto newProgram = breedBreadth(programs[first], programs[second], toRootI, fromRootI, maxSize);
    programs.push_back(newProgram);
  }
}

void mutate(Programs & programs) {
  size_t programI = rangedRandom(Range{ 0, static_cast<int>(programs.size()) });
  auto program(programs[programI]);
  size_t point = rangedRandom(Range{ 0, static_cast<int>(program.size()) });
  auto operation = program[point];
  auto arity = arities[operation];
  auto newOperation = rangedRandom(arityRanges[arity]);
  program[point] = newOperation;
  programs.push_back(program);
}

size_t getBranchLenDepth(CRProgram program, size_t startI) {
  size_t len = 1;
  size_t toProceed = arities[program[startI]];
  while (toProceed > 0) {
    toProceed += getArity(program, startI + len);
    --toProceed;
    ++len;
  }
  return len;
}
Program breedDepth(CRProgram from, CRProgram to, size_t fromRootI, size_t toRootI) {
  auto newProgram = to;
  newProgram.erase(newProgram.begin() + toRootI, 
    newProgram.begin() + toRootI + getBranchLenDepth(to, toRootI));
  newProgram.insert(newProgram.begin() + toRootI,
    from.begin() + fromRootI, 
    from.begin() + fromRootI + getBranchLenDepth(from, fromRootI));
  return newProgram;
}
void crossoverDepth(Programs & programs) {
  while (programs.size() < nPrograms) {
    auto from = programs[randBig(dev) % programs.size()];
    auto to = programs[randBig(dev) % programs.size()];
    size_t fromRootI = randBig(dev) % from.size();
    size_t toRootI = randBig(dev) % to.size();
    auto newProgram = breedDepth(from, to, fromRootI, toRootI);
    if (newProgram.size() <= maxSize && getBranchLenDepth(newProgram, 0) <= maxDepth) {
      programs.push_back(newProgram);
    }
  }
}
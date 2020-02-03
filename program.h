double proceed(CRProgram program, double x) {
  std::deque<double> deq;
  for (auto it = program.rbegin(); it != program.rend(); ++it) {
    auto operationId = *it;
    std::vector<double> args;
    if (arities[operationId] == 1) {
      args.push_back(deq.front());
      deq.pop_front();
    }
    else if (arities[operationId] == 2) {
      args.push_back(deq.front());
      deq.pop_front();
      args.push_back(deq.front());
      deq.pop_front();
      std::reverse(args.begin(), args.end());
    }
    deq.push_back(proceed(operationId, args, x));
  }
  return deq.front();
}
Indexes getLevelSizes(CRProgram program) {
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
Indexes getLevelStarts(CRProgram program) {
  auto const sizes = getLevelSizes(program);
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
Indexes getLevelStops(CRProgram program) {
  auto stops = getLevelStarts(program);
  stops.push_back(program.size());
  return stops;
}
size_t getLevelI(size_t i, std::vector<size_t> const & levelStops) {
  size_t levelI = 0;
  while (i >= levelStops[levelI + 1]) {
    ++levelI;
  }
  return levelI;
}
std::vector<size_t> markChildren(CRProgram program, size_t rootI) {
  auto stops = getLevelStops(program);
  auto levelI = getLevelI(rootI, stops);
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
void killChildren(Program & program, size_t rootI) {
  std::vector<size_t> toKill = markChildren(program, rootI);
  for (int i = toKill.size() - 2; i >= 0; i -= 2) {
    program.erase(program.begin() + toKill[i], program.begin() + toKill[i + 1]);
  }
}
Program breed(CRProgram to, CRProgram from, size_t toRootI, size_t fromRootI, size_t maxSize) {
  auto newProgram(to);
  killChildren(newProgram, toRootI);
  newProgram[toRootI] = getTerminal(); // to make newProgram valid tree after killing children
  auto branchIntervals = markChildren(from, fromRootI);
  auto levelStarts = getLevelStarts(newProgram);
  Indexes insertionPoints;
  auto point = toRootI;
  auto levelI = getLevelI(toRootI, getLevelStops(newProgram));
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
  if (newProgram.size() > maxSize || getLevelSizes(newProgram).size() > maxDepth) {
    return from;
  }
  else {
    return newProgram;
  }
}
class Program {

public:

  static Program terminal()
  {
    return Program({ getRandTerminalId() });
  }

  static Program random(size_t maxDepth)
  {
    return Program(getRandomProgram(maxDepth));
  }

  Program(std::vector<Id> const & initProgram) 
  : _program(initProgram)
  {
    _fitness = 0;
    for (int i = 0; i < 10; ++i) {
      //double x = static_cast<double>(rand()) / RAND_MAX * 10;
      double x = i + 1;
      std::vector<double> memory(10, 0);
      _fitness += abs(goal(x) - proceed(0, now(), x, memory));
    }
  }

  double fitness() const
  {
    return _fitness;
  }

  Id node(size_t i) const
  {
    return _program[i];
  }

  size_t arity(size_t i) const
  {
    return operations[_program[i]].arity;
  }

  std::string name(size_t i) const
  {
    return operations[_program[i]].name;
  }

  size_t size() const
  {
    return _program.size();
  }

  Program getSubtreeMutated(size_t maxSize, size_t maxDepth) const
  {
    while (true) {
      auto newBranch = getRandomProgram(maxDepth);
      auto newProgram = _program;
      auto point = rangedRandom(Range{ 0, static_cast<int>(_program.size()) });
      eraseBranch(newProgram, point);
      newProgram.insert(newProgram.begin() + point,
        newBranch.begin(),
        newBranch.begin() + getBranchLen(newBranch, 0));
      if (valid(newProgram, maxSize, maxDepth)) {
        return newProgram;
      }
    }
  }

  size_t childI(size_t parentI, size_t childSiblingI) const
  {
    if (childSiblingI == 0)
    {
      return parentI + 1;
    }
    else if (childSiblingI == 1)
    {
      return parentI + 1 + getBranchLen(_program, parentI + 1);
    }
  }

  std::vector<Id> const & program() const
  {
    return _program;
  }

private:

  std::vector<Id> _program;

  double _fitness;

  double proceed(size_t i, TimePoint const & startTime,
    Input x, std::vector<double> & memory) 
  {
    auto id = _program[i];
    auto _arity = arity(i);
    auto op = operations[id].op;
    if (_arity == 0) {
      switch (op) {
      case Operations::one:
        return 1;
      case Operations::x:
        return x;
      default: return 0;
      }
    }
    else if (_arity == 1) {
      auto arg = proceed(i + 1, startTime, x, memory);
      switch (op) {
      case Operations::sin:
        return sin(arg);
      case Operations::minus:
        return -arg;
      case Operations::getFromMemory:
        return memory[moduloDouble(arg, memory.size())];
      default: return 0;
      }
    }
    else if (_arity == 2) {
      auto arg1 = proceed(i + 1, startTime, x, memory);
      auto index2 = i + 1 + getBranchLen(_program, i + 1);
      auto arg2 = proceed(index2, startTime, x, memory);
      switch (op) {
      case Operations::plus:
        return arg1 + arg2;
      case Operations::multiply:
        return arg1 * arg2;
      case Operations::setToMemory:
        return memory[moduloDouble(arg1, memory.size())] = arg2;
      case Operations::whilePositiveDecrement:
        return whilePositiveDecrement(i, startTime, x, memory);
      default: return 0;
      }
    }
    return 0;
  }

  double whilePositiveDecrement(size_t i, TimePoint const & startTime,
    Input x, std::vector<double> & memory)
  {
    while (true) 
    {
      size_t memoryIndex = moduloDouble(proceed(i + 1, startTime, x, memory), memory.size());
      std::chrono::microseconds timeElapsed =
        std::chrono::duration_cast<std::chrono::microseconds>(now() - startTime); //do not use auto keyword
      if (memory[memoryIndex] < 0 || timeElapsed.count() > 100) {
        return 0;
      }
      else {
        --memory[memoryIndex];
        auto index2 = childI(i, 1);
        proceed(index2, startTime, x, memory);
      }
    }
  }

};

size_t getBranchLen(CRProgram program, size_t startI) 
{
  size_t len = 1;
  size_t toProceed = operations[program[startI]].arity;
  while (toProceed > 0) {
    toProceed += operations[program[startI + len]].arity;
    --toProceed;
    ++len;
  }
  return len;
}
void eraseBranch(Program_ & program, size_t i) {
  program.erase(program.begin() + i,
    program.begin() + i + getBranchLen(program, i));
}
Program_ breed(CRProgram from, CRProgram to, size_t fromRootI, size_t toRootI) {
  auto newProgram = to;
  eraseBranch(newProgram, toRootI);
  newProgram.insert(newProgram.begin() + toRootI,
    from.begin() + fromRootI, 
    from.begin() + fromRootI + getBranchLen(from, fromRootI));
  return newProgram;
}
bool valid(CRProgram program, size_t maxSize, size_t maxDepth) {
  return program.size() <= maxSize && getBranchLen(program, 0) <= maxDepth;
}
void crossover(std::vector<Program> & programs, size_t nPrograms, size_t maxSize, size_t maxDepth) {
  while (programs.size() < nPrograms) {
    auto from = programs[randBig(rng) % programs.size()];
    auto to = programs[randBig(rng) % programs.size()];
    size_t fromRootI = randBig(rng) % from.size();
    size_t toRootI = randBig(rng) % to.size();
    auto newProgram = breed(from.program(), to.program(), fromRootI, toRootI);
    if (valid(newProgram, maxSize, maxDepth)) {
      programs.push_back(newProgram);
    }
    else {
      //programs.push_back(from);
    }
  }
}

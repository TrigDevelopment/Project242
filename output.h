void output(CRProgram program) {
  std::cout << "Tree: " << std::endl;
  std::cout << tformDepth(program, 0, 0) << std::endl;
  std::cout << mformDepth(program, 0) << std::endl;
  std::cout << std::endl;
}
void output(std::vector<Program> programs) {
  for (auto const & program : programs) {
    output(program);
  }
}
template <typename T> void output(T const & elements) {
  for (auto const & element : elements) {
    std::cout << element << ' ';
  }
  std::cout << std::endl;
}
std::string mform(CRProgram program) {
  std::deque<std::string> deq;
  for (auto it = program.rbegin(); it != program.rend(); ++it) {
    auto operationId = *it;
    std::vector<std::string> args;
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
    std::string next;
    switch (operationId) {
    case 0:
      next = "1";
      break;
    case 1:
      next = "x";
      break;
    case 2:
      next = "(sin(" + args[0] + "))";
      break;
    case 3:
      next = "(" + args[0] + "+" + args[1] + ")";
      break;
    case 4:
      next = "(" + args[0] + "*" + args[1] + ")";
      break;
    }
    deq.push_back(next);
  }
  return deq.front();
}
std::string getSpaces(int nRepetitions) {
  std::string string("");
  for (int i = 0; i < nRepetitions; ++i) {
    string += ' ';
  }
  return string;
}
std::string tformBreadth(CRProgram program) {
  std::string str;
  auto lefts = getLevelStartsBreadth(program);
  std::vector<int> stack;
  for (size_t x = 0; x < program.size(); ++x) {
    auto i = lefts[stack.size()];
    auto id = program[i];
    auto arity = arities[id];
    str += getSpaces(stack.size() * 1)
      + names[id] + "[" + std::to_string(i) + "]"/* + ":" + std::to_string(arity)*/ + "\n";
    ++lefts[stack.size()];
    if (!stack.empty()) {
      --stack[stack.size() - 1];
    }
    stack.push_back(arity);
    while (!stack.empty() && stack[stack.size() - 1] == 0) {
      stack.pop_back();
    }
  }
  return str;
}

std::string tformDepth(CRProgram program, size_t i, int indent) {
  auto str = getSpaces(indent);
  str += getName(program, i) + "[" + std::to_string(i) + "]\n";
  auto const arity = arities[program[i]];
  ++i;
  for (size_t arityI = 0; arityI < arity; ++arityI) {
    str += tformDepth(program, i, indent + 1);
    i += getBranchLenDepth(program, i);
  }
  return str;
}
std::string mformDepth(CRProgram program, size_t startI) {
  std::string str;
  auto id = program[startI];
  switch (id) {
  case 0: return "1";
  case 1: return "x";
  case 2: return "(sin(" + mformDepth(program, startI + 1) + "))";
  case 3: return "(" + mformDepth(program, startI + 1) 
    + "+" + mformDepth(program, startI + 1 + getBranchLenDepth(program, startI + 1)) + ")";
  case 4: return "(" + mformDepth(program, startI + 1)
    + "*" + mformDepth(program, startI + 1 + getBranchLenDepth(program, startI + 1)) + ")";
  default: return 0;
  }
}
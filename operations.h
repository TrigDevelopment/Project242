enum class Operations {
  one, x,
  sin, minus, getFromMemory,
  plus, multiply, setToMemory, whilePositiveDecrement
};
std::vector<Operation> const operations = {
  Operation{"1", 0, Operations::one}, 
    Operation{"x", 0, Operations::x},
  Operation{"sin", 1, Operations::sin}, 
    Operation{"-", 1, Operations::minus}, 
    Operation{"v[]", 1, Operations::getFromMemory},
  Operation{"+", 2, Operations::plus},
    Operation{"*", 2, Operations::multiply},
    Operation{"v[]=", 2, Operations::setToMemory},
    Operation{"whilePositiveDecrement", 2, Operations::whilePositiveDecrement}
};

std::vector<Range> const arityRanges = { Range{0, 2}, Range{2, 5}, Range{5, 9} };

double whilePositiveDecrement(CRProgram program, size_t i, TimePoint const & startTime, 
  Input x, std::vector<double> & memory);
double proceed(CRProgram program, size_t i, TimePoint const & startTime,
Input x, std::vector<double> & memory) {
  auto id = program[i];
  auto arity = getArity(program, i);
  auto name = getName(program, i);
  auto op = operations[id].op;
  if (arity == 0) {
    switch (op) {
      case Operations::one:
        return 1;
      case Operations::x:
        return x;
      default: return 0;
    }
  }
  else if (arity == 1) {
    auto arg = proceed(program, i + 1, startTime, x, memory);
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
  else if (arity == 2) {
    auto arg1 = proceed(program, i + 1, startTime, x, memory);
    auto index2 = i + 1 + getBranchLen(program, i + 1);
    auto arg2 = proceed(program, index2, startTime, x, memory);
    switch (op) {
    case Operations::plus:
      return arg1 + arg2;
    case Operations::multiply:
      return arg1 * arg2;
    case Operations::setToMemory:
      return memory[moduloDouble(arg1, memory.size())] = arg2;
    case Operations::whilePositiveDecrement:
      return whilePositiveDecrement(program, i, startTime, x, memory);
    default: return 0;
    }
  }
  return 0;
}
std::string mform(CRProgram program, size_t startI) {
  std::string str;
  auto id = program[startI];
  auto arity = getArity(program, startI);
  auto op = operations[id].op;
  if (arity == 0) {
    switch (op) {
    case Operations::one:
      return "1";
    case Operations::x:
      return "x";
    default: return "0";
    }
  }
  else if (arity == 1) {
    auto arg = mform(program, startI + 1);
    switch (op) {
    case Operations::sin:
      return "(sin" + arg + ")";
    case Operations::minus:
      return "(-" + arg + ")";
    case Operations::getFromMemory:
      return "v[" + arg + "]";
    default: return "0";
    }
  }
  else if (arity == 2) {
    auto arg1 = mform(program, startI + 1);
    auto index2 = startI + 1 + getBranchLen(program, startI + 1);
    auto arg2 = mform(program, index2);
    switch (op) {
    case Operations::plus:
      return "(" + arg1 + "+" + arg2 + ")";
    case Operations::multiply:
      return  "(" + arg1 + "*" + arg2 + ")";
    case Operations::setToMemory:
      return "(v[" + arg1 + "]=" + arg2 + ")";
    case Operations::whilePositiveDecrement:
      return "wPD(" + arg1 + "){" + arg2 + "}";
    default: return "0";
    }
  }
  return "?";
}
Id opId(std::string const & name) {
  for (Id i = 0; i < operations.size(); ++i) {
    if (operations[i].name == name) {
      return i;
    }
  }
  return 0;
}
Id getTerminal() {
  return opId("1");
}

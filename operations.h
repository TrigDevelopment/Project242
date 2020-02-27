

std::vector<Range> const arityRanges = { Range{0, 2}, Range{2, 5}, Range{5, 9} };

std::string mform(Program const & program, size_t startI) {
  std::string str;
  auto id = program.node(startI);
  auto arity = program.arity(startI);
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
    auto index2 = program.childI(startI, 1);
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

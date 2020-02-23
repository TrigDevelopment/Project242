void output(CRProgram program, bool noMForm = false) {
  std::cout << "tform:" << std::endl;
  std::cout << tform(program, 0, 0) << std::endl;
  if (!noMForm) {
    std::cout << "mform:" << std::endl;
    std::cout << mform(program, 0) << std::endl << std::endl;
  }
  std::cout << "Fitness: " << getFitness(program) << std::endl << std::endl;
  std::cout << std::endl;
}
void output(std::vector<Program> programs) {
  for (auto const & program : programs) {
    output(program);
  }
}

std::string tform(CRProgram program, size_t i, int indent) {
  auto str = getSpaces(indent);
  str += getName(program, i) + "[" + std::to_string(i) + "]\n";
  auto const arity = arities[program[i]];
  ++i;
  for (size_t arityI = 0; arityI < arity; ++arityI) {
    str += tform(program, i, indent + 1);
    i += getBranchLen(program, i);
  }
  return str;
}
std::string mform(CRProgram program, size_t startI) {
  std::string str;
  auto id = program[startI];
  switch (id) {
  case 0: return "1";
  case 1: return "x";
  case 2: return "(sin(" + mform(program, startI + 1) + "))";
  case 3: return "(" + mform(program, startI + 1) 
    + "+" + mform(program, startI + 1 + getBranchLen(program, startI + 1)) + ")";
  case 4: return "(" + mform(program, startI + 1)
    + "*" + mform(program, startI + 1 + getBranchLen(program, startI + 1)) + ")";
  default: return 0;
  }
}
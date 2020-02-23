std::string mform(CRProgram program, size_t startI);
void output(CRProgram program, bool noMForm = false) {
  std::ofstream log;
  auto timeStamp = std::chrono::system_clock::now();
  std::string name("logs/");
  using namespace date;
  std::stringstream str;
  str << std::chrono::system_clock::now();
  name += str.str();
  name += ".txt";
  std::replace(name.begin(), name.end(), ':', '^');
  log.open(name);

  std::cout << "tform:" << std::endl;
  log << "tform:" << std::endl;
  std::cout << tform(program, 0, 0) << std::endl;
  log << tform(program, 0, 0) << std::endl;
  if (!noMForm) {
    std::cout << "mform:" << std::endl;
    log << "mform:" << std::endl;
    std::cout << mform(program, 0) << std::endl << std::endl;
    log << mform(program, 0) << std::endl << std::endl;
  }
  std::cout << "Fitness: " << getFitness(program) << std::endl << std::endl;
  log << "Fitness: " << getFitness(program) << std::endl << std::endl;
  log.close();
}
void output(std::vector<Program> programs) {
  for (auto const & program : programs) {
    output(program);
  }
}

std::string tform(CRProgram program, size_t i, int indent) {
  auto str = getSpaces(indent);
  str += getName(program, i) + "[" + std::to_string(i) + "]\n";
  auto const arity = getArity(program, i);
  ++i;
  for (size_t arityI = 0; arityI < arity; ++arityI) {
    str += tform(program, i, indent + 1);
    i += getBranchLen(program, i);
  }
  return str;
}

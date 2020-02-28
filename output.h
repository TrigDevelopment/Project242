void output(Program const & program, 
  Params const & params = releaseParams, bool noMForm = false) 
{
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

  log << "freeSpaceForBreed: " << params.freeSpaceForBreed() << std::endl;
  log << "maxDepth: " << params.maxDepth() << std::endl;
  log << "maxSize: " << params.maxSize() << std::endl;
  log << "nGenerations: " << params.nGenerations() << std::endl;
  log << "nMutationsPerGeneration: " << params.nMutationsPerGeneration() << std::endl;
  log << "nPopulations: " << params.nPopulations() << std::endl;
  log << "nPrograms: " << params.nPrograms() << std::endl;

  std::cout << "tform:" << std::endl;
  log << "tform:" << std::endl;
  std::cout << tform(program, 0, 0) << std::endl;
  log << tform(program, 0, 0) << std::endl;

  std::cout << "pform: " << std::endl;
  log << "pform:" << std::endl;
  std::cout << pform(program, 0) << std::endl;
  log << pform(program, 0) << std::endl;

  //std::cout << "cform: " << std::endl;
  //log << "cform:" << std::endl;
  //std::cout << cform(program) << std::endl;
  //log << cform(program) << std::endl;

  if (!noMForm) {
    std::cout << "mform:" << std::endl;
    log << "mform:" << std::endl;
    std::cout << mform(program, 0) << std::endl << std::endl;
    log << mform(program, 0) << std::endl << std::endl;
  }
  std::cout << "Fitness: " << program.fitness() << std::endl << std::endl;
  log << "Fitness: " << program.fitness() << std::endl << std::endl;
  log.close();
}
void output(std::vector<Program_> programs) {
  for (auto const & program : programs) {
    output(program);
  }
}

std::string tform(Program const & program, size_t i, int indent) {
  auto str = getSpaces(indent);
  str += program.name(i) + "[" + std::to_string(i) + "]\n";
  auto arity = program.arity(i);
  ++i;
  for (size_t arityI = 0; arityI < arity; ++arityI) {
    str += tform(program, i, indent + 1);
    i += program.branchSize(i);
  }
  return str;
}
std::string pform(Program const & program, size_t i) {
  std::string str;
  str += program.name(i);
  str += " ";
  auto arity = program.arity(i);
  ++i;
  for (size_t arityI = 0; arityI < arity; ++arityI) {
    str += pform(program, i);
    i += program.branchSize(i);
  }
  return str;
}
std::string cform(Program program) {
  std::string str;
  for (int i = 0; i < 10; ++i) {
    //double x = static_cast<double>(rand()) / RAND_MAX * 10;
    double x = i + 1;

    //str += "  (" + std::to_string(goal(x)) + " " + std::to_string(proceed(program, x)) + ")";
    str += "\n";
  }
  return str;
}
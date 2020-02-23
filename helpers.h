std::random_device dev;
std::mt19937_64 rng(dev());
RandomInt randBig(0, std::numeric_limits<int>::max());

auto getArity(CRProgram program, size_t i) {
  return operations[program[i]].arity;
}
auto getName(CRProgram program, size_t i) {
  return operations[program[i]].name;
}
int rangedRandom(Range const & range) {
  return randBig(rng) % (range.end - range.start) + range.start;
}
Id getRandOpId() {
  return rangedRandom({0, static_cast<int>(operations.size() - 1) });
}
Id getRandTerminalId() {
  return rangedRandom(arityRanges[0]);
}
std::string getSpaces(int nRepetitions) {
  std::string string("");
  for (int i = 0; i < nRepetitions; ++i) {
    string += ' ';
  }
  return string;
}
size_t getRandomNodeI(Program const & program) {
  return rangedRandom(Range{ 0, static_cast<int>(program.size()) });
}

std::random_device dev;
std::mt19937_64 rng(dev());
RandomInt randBig(0, std::numeric_limits<int>::max());

size_t getArity(CRProgram program, size_t i) {
  return operations[program[i]].arity;
}
std::string getName(CRProgram program, size_t i) {
  return operations[program[i]].name;
}
int rangedRandom(Range const & range) {
  return randBig(rng) % (range.end - range.start) + range.start;
}
Id getRandOpId() {
  return rangedRandom({0, static_cast<int>(operations.size()) });
}
Id getRandTerminalId() {
  return rangedRandom(arityRanges[0]);
}
Id getRandNonTerminalId() {
  return rangedRandom({ arityRanges[1].start, static_cast<int>(operations.size()) });
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
size_t moduloDouble(double value, size_t m) {
  int intValue = static_cast<int>(llround(value));
  return modulo(intValue, m);
}
size_t modulo(int value, size_t m) {
  int mod = value % static_cast<int>(m);
  if (value < 0) {
    mod += m;
  }
  return mod % m;
}
std::chrono::system_clock::time_point now() {
  return std::chrono::system_clock::now();
}

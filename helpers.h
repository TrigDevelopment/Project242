std::random_device dev;
std::mt19937 rng(dev());
RandomInt randAll(0, arities.size() - 1);
RandomInt randTerminals(0, maxTerminalId);
RandomInt randBig(0, std::numeric_limits<int>::max());

Arity getArity(CRProgram program, size_t i) {
  return arities[program[i]];
}
std::string getName(CRProgram program, size_t i) {
  return names[program[i]];
}
Id getRandOpId() {
  return randAll(rng);
}
Id getRandTerminalId() {
  return randTerminals(rng);
}
int rangedRandom(Range const & range) {
  return randBig(dev) % (range.end - range.start) + range.start;
}
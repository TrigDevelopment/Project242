int maxTerminalId = 1;

std::vector<Operation> operations = {
  Operation{"1", 0}, Operation{"x", 0},
  Operation{"sin", 1}, 
  Operation{"+", 2}, Operation{"*", 2}
};
std::vector<Range> arityRanges = { Range{0, 2}, Range{2, 3}, Range{3, 5} };
Arities createArities() {
  Arities res;
  for (auto op : operations) {
    res.push_back(op.arity);
  }
  return res;
}
Names createNames() {
  Names res;
  for (auto op : operations) {
    res.push_back(op.name);
  }
  return res;
}
Arities arities = createArities();
Names names = createNames();

Id opId(std::string name) {
  for (Id i = 0; i < operations.size(); ++i) {
    if (operations[i].name == name) {
      return i;
    }
  }
  return 0;
}

double proceedBreadth(Id id, std::vector<double> const & deq, size_t argsStart, Input x) {
  switch (id) {
  case 0: return 1;
  case 1: return x;
  case 2: return sin(deq[argsStart]);
  case 3: return deq[argsStart] + deq[argsStart + 1];
  case 4: return deq[argsStart] * deq[argsStart + 1];
  default: return 0;
  }
}
double proceedDepth(CRProgram program, size_t i, Input x) {
  auto id = program[i];
  switch (id) {
  case 0: return 1;
  case 1: return x;
  case 2: return sin(proceedDepth(program, i + 1, x));
  case 3: return proceedDepth(program, i + 1, x) 
    + proceedDepth(program, i + 1 + getBranchLenDepth(program, i + 1), x);
  case 4: return proceedDepth(program, i + 1, x) 
    * proceedDepth(program, i + 1 + getBranchLenDepth(program, i + 1), x);
  default: return 0;
  }
}
Id getTerminal() {
  return opId("1");
}

int maxTerminalId = 1;

std::vector<Operation> operations = {
  Operation{"1", 0}, Operation{"x", 0},
  Operation{"sin", 1}, Operation{"-", 1},
  Operation{"+", 2}, Operation{"*", 2}
};
std::vector<Range> arityRanges = { Range{0, 2}, Range{2, 4}, Range{4, 6} };
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

double proceed(CRProgram program, size_t i, Input x) {
  auto id = program[i];
  switch (id) {
  case 0: return 1;
  case 1: return x;

  case 2: return sin(proceed(program, i + 1, x));
  case 3: return -proceed(program, i + 1, x);

  case 4: return proceed(program, i + 1, x) 
    + proceed(program, i + 1 + getBranchLen(program, i + 1), x);
  case 5: return proceed(program, i + 1, x) 
    * proceed(program, i + 1 + getBranchLen(program, i + 1), x);
  default: return 0;
  }
}
std::string mform(CRProgram program, size_t startI) {
  std::string str;
  auto id = program[startI];
  switch (id) {
  case 0: return "1";
  case 1: return "x";

  case 2: return "(sin" + mform(program, startI + 1) + ")";
  case 3: return "(-" + mform(program, startI + 1) + ")";

  case 4: return "(" + mform(program, startI + 1)
    + "+" + mform(program, startI + 1 + getBranchLen(program, startI + 1)) + ")";
  case 5: return "(" + mform(program, startI + 1)
    + "*" + mform(program, startI + 1 + getBranchLen(program, startI + 1)) + ")";
  default: return 0;
  }
}
Id getTerminal() {
  return opId("1");
}

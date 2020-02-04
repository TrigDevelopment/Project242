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

double proceed(int id, std::vector<double> const & args, double x) noexcept {
  switch (id) {
  case 0: return 1;
  case 1: return x;
  case 2: return sin(args[0]);
  case 3: return args[0] + args[1];
  case 4: return args[0] * args[1];
  default: return 0;
  }
}
Id getTerminal() {
  return opId("1");
}
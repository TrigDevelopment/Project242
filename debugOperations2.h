int maxTerminalId = 29;
size_t terminalsStart = 29;

std::vector<Operation> operations = {
  Operation{"A_0", 0}, Operation{"A_1", 0}, Operation{"A_2", 0},
  Operation{"A_3", 0}, Operation{"A_4", 0}, Operation{"A_5", 0},
  Operation{"A_6", 0}, Operation{"A_7", 0}, Operation{"A_8", 0},
  Operation{"A_9", 0}, Operation{"A_10", 0}, Operation{"A_11", 0},
  Operation{"A_12", 0}, Operation{"A_13", 0}, Operation{"A_14", 0},
  Operation{"A_15", 0}, Operation{"A_16", 0}, Operation{"A_17", 0},
  Operation{"A_18", 0}, Operation{"A_19", 0}, Operation{"A_20", 0},
  Operation{"A_21", 0}, Operation{"A_22", 0}, Operation{"A_23", 0},
  Operation{"A_24", 0}, Operation{"A_25", 0}, Operation{"A_26", 0},
  Operation{"A_27", 0}, Operation{"A_28", 0}, Operation{"A_29", 0},

  Operation{"B_0", 1}, Operation{"B_1", 1}, Operation{"B_2", 1},
  Operation{"B_3", 1}, Operation{"B_4", 1}, Operation{"B_5", 1},
  Operation{"B_6", 1}, Operation{"B_7", 1}, Operation{"B_8", 1},
  Operation{"B_9", 1}, Operation{"B_10", 1}, Operation{"B_11", 1},
  Operation{"B_12", 1}, Operation{"B_13", 1}, Operation{"B_14", 1},

  Operation{"C_0", 2}, Operation{"C_1", 2}, Operation{"C_2", 2},
  Operation{"C_3", 2}, Operation{"C_4", 2}, Operation{"C_5", 2},
  Operation{"C_6", 2}, Operation{"C_7", 2}, Operation{"C_8", 2},

  Operation{"D_0", 3}, Operation{"D_1", 3}, Operation{"D_2", 3},
  Operation{"D_3", 3}, Operation{"D_4", 3}, Operation{"D_5", 3},

  Operation{"E_0", 4}, Operation{"E_1", 4}, Operation{"E_2", 4},

  Operation{"F_0", 5}, Operation{"F_1", 5}, Operation{"F_2", 5}
};
Id opId(std::string name) {
  for (Id i = 0; i < operations.size(); ++i) {
    if (operations[i].name == name) {
      return i;
    }
  }
}
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

double proceed(int id, std::vector<double> const & args, double x) noexcept {
  switch (id) {
  default: return 0;
  }
}
Id getTerminal() {
  return opId("A_0");
}
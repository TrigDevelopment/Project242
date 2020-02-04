void breedTest() {
  auto to = Program{ *,sin,sin,sin,*,sin,x,1,x };
  auto from = Program{ sin,+,*,1,1,1 };
  breed(to, from, 2, 0) == ?
}

void debugProgram() {
  auto fullProgram = Program{
    opId("D_0"),
      opId("D_0"), opId("D_1"), opId("D_2"),
        opId("C_0"), opId("C_1"), opId("C_2"),
        opId("C_3"), opId("C_4"), opId("C_5"),
        opId("C_6"), opId("C_7"), opId("C_8"),
          opId("A_0"),opId("A_1"),opId("A_2"),opId("A_3"),opId("A_4"),opId("A_5"),
          opId("A_6"),opId("A_7"),opId("A_8"),opId("A_9"),opId("A_10"),opId("A_11"),
          opId("A_12"),opId("A_13"),opId("A_14"),opId("A_15"),opId("A_16"),opId("A_17"),
  };
  auto smallerProgram = Program{
    opId("D_0"),
      opId("B_0"), opId("D_1"), opId("B_2"),
        opId("C_0"),
        opId("C_3"), opId("C_4"), opId("C_5"),
        opId("A_20"),
          opId("A_0"),opId("A_1"),
          opId("A_6"),opId("A_7"),opId("A_8"),opId("A_9"),opId("A_10"),opId("A_11")
  };
  auto smallProgram = Program{
    opId("D_4"),
      opId("A_20"),
      opId("A_21"),
      opId("A_22")
  };
  auto otherSmallProgram = Program{
    opId("B_1"),
      opId("A_7")
  };
  auto breededProgram = breed(smallerProgram, otherSmallProgram, 2, 0, maxSize);
  std::ofstream primes("tree.txt");
  primes << tform(breededProgram) << std::endl;
  //primes << tform(otherSmallProgram) << std::endl;
  primes.close();
  //std::cout << tform(fullProgram) << std::endl;
  //killChildren(fullProgram, 0);
  //fullProgram[0] = opId("A_0");
  std::cout << tform(smallerProgram) << std::endl;
  std::cout << tform(breededProgram) << std::endl;
}
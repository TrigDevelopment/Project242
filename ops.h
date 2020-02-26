double whilePositiveDecrement(CRProgram program, size_t i, TimePoint const & startTime,
  Input x, std::vector<double> & memory)
{
  while (true) {
    size_t memoryIndex = moduloDouble(proceed(program, i + 1, startTime, x, memory), memory.size());
    std::chrono::microseconds timeElapsed =
      std::chrono::duration_cast<std::chrono::microseconds>(now() - startTime); //do not use auto keyword
    if (memory[memoryIndex] < 0 || timeElapsed.count() > 10) {
      return 0;
    }
    else {
      --memory[memoryIndex];
      auto index2 = i + 1 + getBranchLen(program, i + 1);
      proceed(program, index2, startTime, x, memory);
    }
  }
}
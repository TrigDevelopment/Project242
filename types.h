using RandomInt = std::uniform_int_distribution<std::mt19937::result_type>;
using Id = unsigned char;
using Program = std::vector<Id>;
using Programs = std::vector<Program>;
using CRProgram = Program const &;
using Arity = size_t;
using Arities = std::vector<size_t>;
using Names = std::vector<std::string>;
using Indexes = std::vector<size_t>;
using CRIndexes = std::vector<size_t> const &;
using Input = double;
std::string tform(CRProgram program, size_t i, int indent);
std::string mform(CRProgram program, size_t startI);
size_t getBranchLenDepth(CRProgram program, size_t startI);
struct Operation {
  std::string name;
  int arity;
};
struct Range {
  int start;
  int end;
};
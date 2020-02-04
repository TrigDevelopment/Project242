using RandomInt = std::uniform_int_distribution<std::mt19937::result_type>;
using Id = unsigned char;
using Program = std::vector<Id>;
using Programs = std::vector<Program>;
using CRProgram = Program const &;
using Arities = std::vector<int>;
using Names = std::vector<std::string>;
using Indexes = std::vector<size_t>;
using CRIndexes = std::vector<size_t> const &;
std::string tform(CRProgram program);
std::string mform(CRProgram program);
struct Operation {
  std::string name;
  int arity;
};
struct Range {
  int start;
  int end;
};
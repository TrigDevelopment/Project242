using RandomInt = std::uniform_int_distribution<std::mt19937::result_type>;
using Program = std::vector<char>;
using Programs = std::vector<Program>;
using CRProgram = std::vector<char> const &;
using Arities = std::vector<int>;
using Names = std::vector<std::string>;
using Id = char;
using Indexes = std::vector<size_t>;
using CRIndexes = std::vector<size_t> const &;
std::string tform(CRProgram program);
struct Operation {
  std::string name;
  int arity;
};
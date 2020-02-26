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
using TimePoint = std::chrono::system_clock::time_point;
std::string tform(CRProgram program, size_t i, int indent);
std::string mform(CRProgram program, size_t startI);
std::string pform(CRProgram program, size_t i);
std::string cform(CRProgram program);
size_t getBranchLen(CRProgram program, size_t startI);
enum class Operations;
size_t getArity(CRProgram program, size_t i);
std::string getName(CRProgram program, size_t i);
size_t modulo(int value, size_t m);
size_t moduloDouble(double value, size_t m);
TimePoint now();
std::string mform(CRProgram program, size_t startI);
double proceed(CRProgram program, size_t i, 
  TimePoint const &, Input x, std::vector<double> & memory);
struct Operation {
  std::string name;
  size_t arity;
  Operations op;
};
struct Range {
  int start;
  int end;
};
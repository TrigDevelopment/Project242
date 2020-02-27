using RandomInt = std::uniform_int_distribution<std::mt19937::result_type>;
using Id = unsigned char;
using Program_ = std::vector<Id>;
class Program;
using CRProgram = Program_ const &;
using Arity = size_t;
using Arities = std::vector<size_t>;
using Names = std::vector<std::string>;
using Indexes = std::vector<size_t>;
using CRIndexes = std::vector<size_t> const &;
using Input = double;
using TimePoint = std::chrono::system_clock::time_point;
using MicroSeconds = std::chrono::microseconds;
std::string tform(Program const & program, size_t i, int indent);
std::string mform(Program const & program, size_t startI);
std::string pform(Program const & program, size_t i);
size_t getBranchLen(CRProgram program, size_t startI);

std::random_device dev;
std::mt19937_64 rng(dev());
RandomInt randBig(0, std::numeric_limits<int>::max());

enum class Operations {
  one, x,
  sin, minus, getFromMemory,
  plus, multiply, setToMemory, whilePositiveDecrement
};
size_t modulo(int value, size_t m);
size_t moduloDouble(double value, size_t m);
TimePoint now();

struct Range;
Id getRandTerminalId();
std::vector<Id> getRandomProgram(size_t maxDepth);
double goal(double x);
struct Operation {
  std::string name;
  size_t arity;
  Operations op;
};
std::vector<Operation> const operations = {
  Operation{"1", 0, Operations::one},
    Operation{"x", 0, Operations::x},
  Operation{"sin", 1, Operations::sin},
    Operation{"-", 1, Operations::minus},
    Operation{"v[]", 1, Operations::getFromMemory},
  Operation{"+", 2, Operations::plus},
    Operation{"*", 2, Operations::multiply},
    Operation{"v[]=", 2, Operations::setToMemory},
    Operation{"whilePositiveDecrement", 2, Operations::whilePositiveDecrement}
};

int rangedRandom(Range const & range);
void eraseBranch(Program_ & program, size_t i);
bool valid(CRProgram program, size_t maxSize, size_t maxDepth);


struct Range {
  int start;
  int end;
};
struct Params {
  virtual size_t nPopulations() const = 0;
  virtual size_t nGenerations() const = 0;
  virtual size_t nPrograms() const = 0;
  virtual size_t freeSpaceForBreed() const = 0;
  virtual size_t nMutationsPerGeneration() const = 0;
  virtual size_t maxSize() const = 0;
  virtual size_t maxDepth() const = 0;
};
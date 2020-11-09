#include <map>

class InstructionMemory {
  private:
    std::map<int, int> memory;
    int count;
  public:
    InstructionMemory();
    ~InstructionMemory();
    void add(int instruction);
    int get(int address);
};

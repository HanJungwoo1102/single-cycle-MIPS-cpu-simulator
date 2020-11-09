#include <map>

class DataMemory {
  private:
    std::map<int, int> memory;

  public:
    DataMemory();
    ~DataMemory();
    int getData(int address);
    void setData(int address, int data);
};

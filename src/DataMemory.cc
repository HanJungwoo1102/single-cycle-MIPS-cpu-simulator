#include "DataMemory.h"

DataMemory::DataMemory() {
}

DataMemory::~DataMemory() {

}

void DataMemory::setData(int address, int data) {
  DataMemory::memory[address] = data;
}

int DataMemory::getData(int address) {
  int count = DataMemory::memory.count(address);

  if (count > 0) {
    int data = DataMemory::memory[address];
    return data;
  }

  return 0xFFFFFFFF;
}

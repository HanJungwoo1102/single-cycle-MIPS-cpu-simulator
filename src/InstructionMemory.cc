#include "InstructionMemory.h"

InstructionMemory::InstructionMemory() {
  InstructionMemory::count = 0;
}

InstructionMemory::~InstructionMemory() {
  
}

void InstructionMemory::add(int instruction) {
  int count = InstructionMemory::count;

  int instructionAddress = count * 4 + 0x00000000;

  InstructionMemory::memory[instructionAddress] = instruction;
  InstructionMemory::count += 1;
}

int InstructionMemory::get(int address) {
  int count = InstructionMemory::memory.count(address);

  if (count > 0) {
    int instruction = InstructionMemory::memory[address];
    return instruction;
  }

  return 0xFFFFFFFF;
}

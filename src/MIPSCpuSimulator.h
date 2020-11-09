#include "DataMemory.h"
#include "InstructionMemory.h"
#include "Register.h"
#include <iostream>

class MIPSCpuSimulator {
  private:
    static const int PC_REGISTER_NUMBER = 31;

    DataMemory dataMemory;
    InstructionMemory instructionMemory;
    Register registerSet;

    int getOp(int inst);
    int getRs(int inst);
    int getRt(int inst);
    int getRd(int inst);
    int getShamt(int inst);
    int getFunct(int inst);
    int getImmediate(int inst);
    int getTargetAddress(int inst);

  public:
    MIPSCpuSimulator();
    ~MIPSCpuSimulator();

    void addInstruction(int instruction);
    void simulate(int n);
    void excuteInstruction(int instructionAddress, int instruction);

    void printRegister();
    void printMemory();
};

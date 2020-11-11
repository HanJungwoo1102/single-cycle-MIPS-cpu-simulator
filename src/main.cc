#include <iostream>
#include <fstream>

#include "MIPSCpuSimulator.h"

const char* REG_PRINT_MODE = "reg";
const char* MEM_PRINT_MODE = "mem";

int main(int argc, char **argv) {
    if (argc > 3) {
        char* fileName = argv[1];
        int simulatedInstructionMaxCount = std::atoi(argv[2]);
        char* printMode = argv[3];

        std::ifstream inFile(fileName, std::ifstream::binary|std::ifstream::ate);

        MIPSCpuSimulator mIPSCpuSimulator = MIPSCpuSimulator();
        if (inFile.is_open()) {
            char* buffer;
            long size = inFile.tellg();
            inFile.seekg(0, std::ifstream::beg);

            buffer = new char[size];

            inFile.read(buffer, size);
            inFile.close();

            for(int index = 0; index < size / 4; index++) {
                int instruction;

                char* is = (char *) &instruction;

                for (int i = 0; i < 4; i++) {
                    is[3 - i] = buffer[index * 4 + i];
                }
                mIPSCpuSimulator.addInstruction(instruction);
            }
        }
        mIPSCpuSimulator.simulate(simulatedInstructionMaxCount);

        if (std::strcmp(printMode, REG_PRINT_MODE) == 0) {
            mIPSCpuSimulator.printRegister();
        } else if (std::strcmp(printMode, MEM_PRINT_MODE) == 0) {
            if (argc == 6) {
                int startMemoryAddress = Util::convertHexStringToInt(argv[4]);
                int printCount = std::atoi(argv[5]);

                mIPSCpuSimulator.printMemory(startMemoryAddress, printCount);
            }
        }
    }
    return 0;
}

#include <iostream>
#include <fstream>

#include "MIPSCpuSimulator.h"
#include "Util.h"

const char* REG_PRINT_MODE = "reg";
const char* MEM_PRINT_MODE = "mem";

int main(int argc, char **argv) {
    std::cout << "================================" << std::endl;
    if (argc > 3) {
        char* fileName = argv[1];
        int simulatedInstructionMaxCount = std::atoi(argv[2]);
        char* printMode = argv[3];

        std::cout << "file name : " << fileName << std::endl;
        std::cout << "N : " << simulatedInstructionMaxCount << std::endl;
        std::cout << "print mode : " << printMode << std::endl;

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

                std::cout << "starting address : " << startMemoryAddress << std::endl;
                std::cout << "number to print : " << printCount << std::endl;

                mIPSCpuSimulator.printMemory();
            }
        }
    }
    std::cout << "================================" << std::endl;

    return 0;
}

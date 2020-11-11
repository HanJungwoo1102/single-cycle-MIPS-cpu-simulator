#include "MIPSCpuSimulator.h"

MIPSCpuSimulator::MIPSCpuSimulator() {
  MIPSCpuSimulator::dataMemory = DataMemory();
  MIPSCpuSimulator::instructionMemory = InstructionMemory();
  MIPSCpuSimulator::registerSet = Register();
}

MIPSCpuSimulator::~MIPSCpuSimulator() {

}

void MIPSCpuSimulator::addInstruction(int instruction) {
  MIPSCpuSimulator::instructionMemory.add(instruction);
}

void MIPSCpuSimulator::simulate(int n) {
  for (int i = 0; i < n; i++) {
    int instructionAddress = MIPSCpuSimulator::registerSet.getRegister(MIPSCpuSimulator::PC_REGISTER_NUMBER);

    int instruction = MIPSCpuSimulator::instructionMemory.get(instructionAddress);
    try {
      MIPSCpuSimulator::excuteInstruction(instructionAddress, instruction);

    } catch(int error) {
      if (error == 1) {
        std::cout << "unknown instruction" << std::endl;
        break;
      }
    }
  }
}

void MIPSCpuSimulator::excuteInstruction(int instructionAddress, int instruction) {
  int op = MIPSCpuSimulator::getOp(instruction);
  int rs = MIPSCpuSimulator::getRs(instruction);
  int rt = MIPSCpuSimulator::getRt(instruction);
  int rd = MIPSCpuSimulator::getRd(instruction);
  int shamt = MIPSCpuSimulator::getShamt(instruction);
  int funct = MIPSCpuSimulator::getFunct(instruction);
  int immediate = MIPSCpuSimulator::getImmediate(instruction);
  int unsignedExtendedImmediate = immediate & 0x0000FFFF;
  int targetAddress = MIPSCpuSimulator::getTargetAddress(instruction);

  int rsData = MIPSCpuSimulator::registerSet.getRegister(rs);
  int rtData = MIPSCpuSimulator::registerSet.getRegister(rt);

  int pc = instructionAddress + 4;

  if (instruction == 0) {
    // printf("nop\n");
  } else if (op == 0 && funct == 32) {
    // printf("add $%d, $%d, $%d\n", rd, rs, rt);
    MIPSCpuSimulator::registerSet.setRegitser(rd, rsData + rtData);
  } else if (op == 0 && funct == 34) {
    // printf("sub $%d, $%d, $%d\n", rd, rs, rt);

    MIPSCpuSimulator::registerSet.setRegitser(rd, rsData - rtData);
  } else if (op == 0 && funct == 36) {
    // printf("and $%d, $%d, $%d\n", rd, rs, rt);

    MIPSCpuSimulator::registerSet.setRegitser(rd, rsData & rtData);
  } else if (op == 0 && funct == 37) {
    // printf("or $%d, $%d, $%d\n", rd, rs, rt);

    MIPSCpuSimulator::registerSet.setRegitser(rd, rsData | rtData);
  } else if (op == 0 && funct == 42) {
    // printf("slt $%d, $%d, $%d\n", rd, rs, rt);

    MIPSCpuSimulator::registerSet.setRegitser(rd, rsData < rtData ? 1 : 0);
  } else if (op == 8) {
    // printf("addi $%d, $%d, %d\n", rt, rs, immediate);

    int data = rsData + immediate;

    MIPSCpuSimulator::registerSet.setRegitser(rt, data);
  } else if (op == 12) {
    // printf("andi $%d, $%d, %d\n", rt, rs, immediate);

    int data = rsData & unsignedExtendedImmediate;

    MIPSCpuSimulator::registerSet.setRegitser(rt, data);
  } else if (op == 13) {
    // printf("ori $%d, $%d, %d\n", rt, rs, immediate);

    int data = rsData | unsignedExtendedImmediate;

    MIPSCpuSimulator::registerSet.setRegitser(rt, data);
  } else if (op == 10) {
    // printf("slti $%d, $%d, %d\n", rt, rs, immediate);

    int data = rsData < immediate ? 1: 0;

    MIPSCpuSimulator::registerSet.setRegitser(rt, data);
  } else if (op == 15) {
    // printf("lui $%d, %d\n", rt, immediate);

    int data = immediate << 16;

    MIPSCpuSimulator::registerSet.setRegitser(rt, data);
  } else if (op == 35) {
    // printf("lw $%d, %d($%d)\n", rt, immediate, rs);
    int memoryAddress = rsData + immediate;

    int data = MIPSCpuSimulator::dataMemory.getData(memoryAddress);

    MIPSCpuSimulator::registerSet.setRegitser(rt, data);
  } else if (op == 43) {
    // printf("sw $%d, %d($%d)\n", rt, immediate, rs);
    int memoryAddress = rsData + immediate;

    MIPSCpuSimulator::dataMemory.setData(memoryAddress, rtData);
  } else if (op == 4) {
    // printf("beq $%d, $%d, %d\n", rs, rt, immediate);

    if (rsData == rtData) {
      pc += immediate * 4;
    }
  } else if (op == 5) {
    // printf("bne $%d, $%d, %d\n", rs, rt, immediate);

    if (rsData != rtData) {
      pc += immediate * 4;
    }
  } else if (op == 2) {
    // printf("j $%d\n", targetAddress);

    pc = targetAddress * 4;
  } else {
    MIPSCpuSimulator::registerSet.setRegitser(MIPSCpuSimulator::PC_REGISTER_NUMBER, pc);
    throw 1;
  }

  MIPSCpuSimulator::registerSet.setRegitser(MIPSCpuSimulator::PC_REGISTER_NUMBER, pc);
}

void MIPSCpuSimulator::printRegister() {
  for (int i = 0; i < 32; i++) {
    int data = MIPSCpuSimulator::registerSet.getRegister(i);
    char hexString[11];
    Util::convertIntToHexString(hexString, data);
    std::cout << "$" << std::dec << i << ": " << hexString << std::endl;
  }
}

void MIPSCpuSimulator::printMemory(int startMemoryAddress, int printCount) {
  for (int i = 0; i < printCount; i++) {
    int memoryAddress = startMemoryAddress + i * 4;
    int data = MIPSCpuSimulator::dataMemory.getData(memoryAddress);
    char hexString[11];
    Util::convertIntToHexString(hexString, data);
    std::cout << hexString << std::endl;
  }
}

int MIPSCpuSimulator::getOp(int inst) {
	return ((inst & 0xFC000000) >> 26) & 0x0000003F;
};

int MIPSCpuSimulator::getRs(int inst) {
	return ((inst & 0x03E00000) >> 21) & 0x0000001F;
};

int MIPSCpuSimulator::getRt(int inst) {
	return ((inst & 0x001F0000) >> 16) & 0x0000001F;
};

int MIPSCpuSimulator::getRd(int inst) {
	return ((inst & 0x0000F800) >> 11) & 0x0000001F;
};

int MIPSCpuSimulator::getShamt(int inst) {
	return ((inst & 0x000007C0) >> 6) & 0x0000001F;
};

int MIPSCpuSimulator::getFunct(int inst) {
	return (inst & 0x0000003F) & 0x0000003F;
};

int MIPSCpuSimulator::getImmediate(int inst) {
	int a = ((inst & 0x0000FFFF) >> 0) & 0x0000FFFF;
	if (a > 32767) {
		return a - 65536;
	}
	return a;
};

int MIPSCpuSimulator::getTargetAddress(int inst) {
	return ((inst & 0x03FFFFFF) >> 0) & 0x03FFFFFF;
};

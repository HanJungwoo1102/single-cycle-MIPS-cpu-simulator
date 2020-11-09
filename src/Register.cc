#include "Register.h"

Register::Register() {
  for (int i = 0; i < Register::registerCount; i++) {
    Register::registerArray[i] = 0;
  }
}

Register::~Register() {
}

bool Register::isRegisterNumber(int registerNumber) {
  if (registerNumber >= 0 && registerNumber < Register::registerCount) {
    return true;
  }
  return false;
}

int Register::getRegister(int registerNumber) {
  if (Register::isRegisterNumber(registerNumber)) {
    return Register::registerArray[registerNumber];
  }
};

int Register::setRegitser(int registerNumber, int data) {
  if (Register::isRegisterNumber(registerNumber)) {
    Register::registerArray[registerNumber] = data;
  }
};

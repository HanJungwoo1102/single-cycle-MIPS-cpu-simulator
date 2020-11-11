#include <iostream>
#include <cstring>

class Util {
  private:
  public:
    static int convertHexStringToInt(char* hexString);
    static char* convertIntToHexString(char* hexString, int integer);
};

#include "Util.h"

int Util::convertHexStringToInt(char* hexString) {
  int result = 0;
  int len = std::strlen(hexString);
  if (len > 2) {
    if (hexString[0] == '0' && hexString[1] == 'x') {
      for (int i = 2; i < len; i++) {
        char hexNumberString = hexString[i];
        int a = len - i - 1;
        int hexNumber;

        switch(hexNumberString){
          case '0':
            hexNumber = 0;
            break;
          case '1':
            hexNumber = 1;
            break;
          case '2':
            hexNumber = 2;
            break;
          case '3':
            hexNumber = 3;
            break;
          case '4':
            hexNumber = 4;
            break;
          case '5':
            hexNumber = 5;
            break;
          case '6':
            hexNumber = 6;
            break;
          case '7':
            hexNumber = 7;
            break;
          case '8':
            hexNumber = 8;
            break;
          case '9':
            hexNumber = 9;
            break;
          case 'a': case 'A':
            hexNumber = 10;
            break;
          case 'b': case 'B':
            hexNumber = 11;
            break;
          case 'c': case 'C':
            hexNumber = 12;
            break;
          case 'd': case 'D':
            hexNumber = 13;
            break;
          case 'e': case 'E':
            hexNumber = 14;
            break;
          case 'f': case 'F':
            hexNumber = 15;
            break;
          default:
            hexNumber = 0;
            break;
        }

        int b = 1;
        for (int i = 0; i < a; i++) {
          b *= 16;
        }

        result += hexNumber * b;
      }
    }
  }

  return result;
}

char* Util::convertIntToHexString(char* hexString, int integer) {
  hexString[0] = '0';
  hexString[1] = 'x';
  for (int i = 0; i < 8; i++) {
    
    int byteInteger = (integer >> 4 * (7 - i)) & (0x0000000f);
    char byteChar;
    switch (byteInteger)
    {
    case 0:
      byteChar = '0';
      break;
    case 1:
      byteChar = '1';
      break;
    case 2:
      byteChar = '2';
      break;
    case 3:
      byteChar = '3';
      break;
    case 4:
      byteChar = '4';
      break;
    case 5:
      byteChar = '5';
      break;
    case 6:
      byteChar = '6';
      break;
    case 7:
      byteChar = '7';
      break;
    case 8:
      byteChar = '8';
      break;
    case 9:
      byteChar = '9';
      break;
    case 10:
      byteChar = 'a';
      break;
    case 11:
      byteChar = 'b';
      break;
    case 12:
      byteChar = 'c';
      break;
    case 13:
      byteChar = 'd';
      break;
    case 14:
      byteChar = 'e';
      break;
    case 15:
      byteChar = 'f';
      break;
    
    default:
      break;
    }

    hexString[2 + i] = byteChar;
  }
  hexString[10] = NULL;
  return hexString;
}

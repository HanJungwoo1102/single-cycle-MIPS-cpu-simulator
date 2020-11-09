class Register {
  private:
    static const int registerCount = 32;
    int registerArray[32];
    bool isRegisterNumber(int registerNumber);
  public:
    Register();
    ~Register();
    int getRegister(int registerNumber);
    int setRegitser(int registerNumber, int data);
};

#pragma once

#include <iostream>

class ISwd;
class IReport;

class IProgrammer
{
public:
  virtual bool Program() = 0;

protected:
  virtual ~IProgrammer() {}
};

class CSTM32F4x7 : public IProgrammer
{
public:
  CSTM32F4x7(ISwd* swd, IReport* report, int size, bool dualBank)
    : mSwd(swd), mReport(report), mSize(size), mDualBank(dualBank)
  {
    std::cout << "Created F437 with size=" << size << std::endl;
  }

  bool Program() override
  {
    std::cout << "Programmed F437" << std::endl;
    return true;
  }

private:
  ISwd* mSwd;
  IReport* mReport;
  int mSize;
  bool mDualBank;
};

class CSPC56 : public IProgrammer
{
public:
  CSPC56(ISwd* swd, IReport* report, int size)
    : mSwd(swd), mReport(report), mSize(size)
  {

  }

  bool Program() override
  {
    std::cout << "Programmed SPC56" << std::endl;
    return true;
  }

private:
  ISwd* mSwd;
  IReport* mReport;
  int mSize;
};
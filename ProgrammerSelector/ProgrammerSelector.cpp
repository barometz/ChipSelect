// ProgrammerSelector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "Selector.h"

class ISwd;
class IReport;

class CProgrammer
{
public:
  virtual bool Program() = 0;

protected:
  virtual ~CProgrammer() {}
};

class CSTM32F4x7 : public CProgrammer
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

class CSPC56 : public CProgrammer
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

const std::vector<Selector> selectors = 
{
  { "STM32F4",
    { 
      { "37",
        { 
          { "?G", {}, [](CreateArgs& args) { return new CSTM32F4x7(args.Swd, args.Report, 10, false); } },
          { "?I", {}, [](CreateArgs& args) { return new CSTM32F4x7(args.Swd, args.Report, 20, true); } }
        }
      } 
    }
  },

  {
    "SPC56",
    { 
       { "33", {}, [](CreateArgs& args) { return new CSPC56(args.Swd, args.Report, 5); } },
       { "34", {}, [](CreateArgs& args) { return new CSPC56(args.Swd, args.Report, 10); } },
       { "3M60", {}, Selector::Parse(selectors, "SPC5633") },
       { "3M64", {}, Selector::Parse(selectors, "SPC5633") }
    }
  }
};

int main()
{
    return 0;
}

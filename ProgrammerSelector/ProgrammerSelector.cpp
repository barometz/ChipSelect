// ProgrammerSelector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "Selector.h"

class CProgrammer
{
public:
  virtual bool Program() = 0;

protected:
  virtual ~CProgrammer() {}
};

class CSTM32F437 : public CProgrammer
{
public:
  CSTM32F437(int i, int size, std::string name) : mSize(size)
  {
    std::cout << "Created F437 with size=" << size << " and name=" << name << std::endl;
  }

  bool Program() override
  {
    std::cout << "Programmed F407" << std::endl;
    return true;
  }

private:
  int mSize;
};

const std::vector<Selector> selectors = 
{
  { "STM32F4", 
    { { "37",
        { { "?G", {}, [](int i) { return new CSTM32F437(i, 10, "STM32F437"); } },
          { "?I", {}, [](int i) { return new CSTM32F437(i, 20, "STM32F437"); } }
        }
      } 
    }
  }
};

int main()
{
    return 0;
}


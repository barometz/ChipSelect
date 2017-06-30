// ProgrammerSelector.cpp : Defines the entry point for the console application.
//

#include <iostream>

#include "Selector.h"
#include "Programmers.h"

class ISwd;
class IReport;

using S = Selector<CProgrammer*, ISwd*, IReport*>;

S::Create Alias(const std::string& deviceName);

const std::vector<S> selectors = 
{
  { "STM32F4",
    { 
      { "37",
        { 
          { "?G", {}, [](auto s, auto r) { return new CSTM32F4x7(s, r, 10, false); } },
          { "?I", {}, [](auto s, auto r) { return new CSTM32F4x7(s, r, 20, true); } }
        }
      } 
    }
  },

  { "SPC56",
    { 
       { "33", {}, [](auto s, auto r) { return new CSPC56(s, r, 5); } },
       { "34", {}, [](auto s, auto r) { return new CSPC56(s, r, 10); } },
       { "3M60", {}, Alias("SPC5633") },
       { "3M64", {}, Alias("SPC5634") }
    }
  }
};

S::Create Alias(const std::string& deviceName)
{
  auto closure = [=](auto s, auto r) -> CProgrammer*
  {
    S::Create creator = S::Parse(selectors, deviceName);
    return creator(s, r);
  };

  return closure;
}

int main(int argc, char* argv[])
{
  auto fn = S::Parse(selectors, "SPC563M64");
  auto p = fn(nullptr, nullptr);
  p->Program();
  return 0;
}

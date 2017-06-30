// ProgrammerSelector.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>

#include "Selector.h"
#include "Programmers.h"

class ISwd;
class IReport;

Create Alias(const std::string& deviceName);

const std::vector<Selector> selectors = 
{
  { "STM32F4",
    { 
      { "37",
        { 
          { "?G", {}, [](auto args) { return new CSTM32F4x7(args.Swd, args.Report, 10, false); } },
          { "?I", {}, [](auto args) { return new CSTM32F4x7(args.Swd, args.Report, 20, true); } }
        }
      } 
    }
  },

  {
    "SPC56",
    { 
       { "33", {}, [](auto args) { return new CSPC56(args.Swd, args.Report, 5); } },
       { "34", {}, [](auto args) { return new CSPC56(args.Swd, args.Report, 10); } },
       { "3M60", {}, Alias("SPC5633") },
       { "3M64", {}, Alias("SPC5634") }
    }
  }
};

Create Alias(const std::string& deviceName)
{
  auto closure = [=](CreateArgs args) -> CProgrammer*
  {
    Create creator = Selector::Parse(selectors, deviceName);
    return creator(args);
  };

  return closure;
}

int main()
{
  CreateArgs args = { nullptr, nullptr };
  auto fn = Selector::Parse(selectors, "SPC563M64");
  auto p = fn(args);
  p->Program();
  return 0;
}

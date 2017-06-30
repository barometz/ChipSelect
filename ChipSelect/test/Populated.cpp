#include "gtest/gtest.h"

#include "Selector.h"
#include "Programmers.h"

using S = Selector<IProgrammer*, ISwd*, IReport*>;

S::TargetFunction Alias(const std::string& deviceName);

const S::List selectors =
{
  { "STM32F4",
    {
      { "37",
        {
          { "?G",{}, [](auto s, auto r) { return new CSTM32F4x7(s, r, 10, false); } },
          { "?I",{}, [](auto s, auto r) { return new CSTM32F4x7(s, r, 20, true); } }
        }
      }
    }
  },

  { "SPC56",
    {
      { "33",{}, [](auto s, auto r) { return new CSPC56(s, r, 5); } },
      { "34",{}, [](auto s, auto r) { return new CSPC56(s, r, 10); } },
      { "3M60",{}, Alias("SPC5633") },
      { "3M64",{}, Alias("SPC5634") }
    }
  }
};

S::TargetFunction Alias(const std::string& deviceName)
{
  auto closure = [=](auto s, auto r) -> IProgrammer*
  {
    S::TargetFunction creator = S::Parse(selectors, deviceName);
    return creator(s, r);
  };

  return closure;
}

TEST(Populated, ValidButShort)
{
  EXPECT_NE(nullptr, S::Parse(selectors, "STM"));
}

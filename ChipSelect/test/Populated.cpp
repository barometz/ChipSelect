#include "gtest/gtest.h"

#include "Selector.h"
#include "Programmers.h"

using S = Selector<IProgrammer*, ISwd*, IReport*>;

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
      { "3M60",{}, S::Alias, "SPC5633" },
      { "3M64",{}, S::Alias, "SPC5634" }
    }
  }
};

TEST(Populated, ValidButTooShort)
{
  EXPECT_FALSE(S::Parse(selectors, "STM").has_value());
}

TEST(Populated, Valid)
{
  EXPECT_TRUE(S::Parse(selectors, "STM32F437?I"));
}

TEST(Populated, Alias)
{
  EXPECT_TRUE(S::Parse(selectors, "SPC563M60"));
}
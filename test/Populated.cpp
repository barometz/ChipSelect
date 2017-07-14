#include "gtest/gtest.h"

#include "Selector.h"

#include "Programmers.h"

using S = Selector<IProgrammer*, IDigitalIO*, ILogger*>;

const std::vector<S> selectors =
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
      { "3M60",{}, S::Alias("SPC5633") },
      { "3M64",{}, S::Alias("SPC5634") }
    },
    [](auto s, auto r) { return new CSPC56(s, r, 0); }
  }
};

TEST(Lookup, Incomplete)
{
  EXPECT_FALSE(S::Parse(selectors, "STM"));
}

TEST(Lookup, Simple)
{
  EXPECT_TRUE(S::Parse(selectors, "SPC5633"));
}

TEST(Lookup, Alias)
{
  EXPECT_TRUE(S::Parse(selectors, "SPC563M60"));
}

TEST(Lookup, Wildcard)
{
  EXPECT_TRUE(S::Parse(selectors, "STM32F437VG"));
}

TEST(Lookup, Longer)
{
  EXPECT_TRUE(S::Parse(selectors, "STM32F437VGAH"));
}

TEST(Lookup, Fallback)
{
  EXPECT_TRUE(S::Parse(selectors, "SPC56Fallback"));
}

TEST(Lookup, Almost)
{
  EXPECT_FALSE(S::Parse(selectors, "STM32F437V"));
}

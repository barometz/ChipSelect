#include "gtest/gtest.h"

#include "Selector.h"

using S = Selector<int>;

class Empty : public testing::Test, public testing::WithParamInterface<std::tuple<std::string, std::vector<S>>>
{

};

TEST_P(Empty, ProvidesFunction)
{
  std::string query;
  std::vector<S> tree;
  std::tie(query, tree) = GetParam();
  ASSERT_NE(nullptr, S::Parse(tree, query));
}

TEST_P(Empty, ProvidesDefaultInit)
{
  std::string query;
  std::vector<S> vec;
  std::tie(query, vec) = GetParam();
  ASSERT_EQ(int(), S::Parse(vec, query)());
}

const std::string queries[] = { "", "Pointless query", "???????" };
const std::vector<S> trees[] =
{
  {},

  { 
    {""} 
  },

  { 
    {"", { { "" } } },
    {},
    {},
    {}
  }
};

using testing::Combine;
using testing::ValuesIn;

INSTANTIATE_TEST_CASE_P(Invalids, Empty, Combine(ValuesIn(queries), ValuesIn(trees)));

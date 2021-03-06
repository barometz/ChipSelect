#include "gtest/gtest.h"

#include "Selector.h"

using S = ChipSelect::Selector<int()>;

class Empty : public testing::Test, public testing::WithParamInterface<std::tuple<std::string, std::vector<S>>>
{

};

TEST_P(Empty, NoResult)
{
  std::string query;
  std::vector<S> tree;
  std::tie(query, tree) = GetParam();
  EXPECT_FALSE(S::Parse(tree, query));
}

const std::string queries[] = { "", "Pointless query", "???????" };
const std::vector<S> trees[] =
{
  { // No nodes
  },

  { // Single empty node
    {""} 
  },

  { // Mixed
    {"", { { "" } } },
    {},
    {},
    {}
  },
  { // Wide
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
    {},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},{},
  },

  { // Deep
    {"", { { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{ { "",{} } } } } } } } } } } } } } } } } } } } } } } } } } } } } } }}
  }
};

using testing::Combine;
using testing::ValuesIn;

INSTANTIATE_TEST_CASE_P(Invalids, Empty, Combine(ValuesIn(queries), ValuesIn(trees)));

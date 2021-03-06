#pragma once

#include <functional>
#include <optional>
#include <vector>

#include "StringTools.h"

namespace ChipSelect
{

template<class Function> class Selector;

template <typename Result, typename ...Args>
// Selects from functions which take Args and return Result
class Selector<Result(Args...)>
{
  using TargetFunction = std::function<Result(Args...)>;
  using MyT = Selector<Result(Args...)>;

public:
  // Selector description
  // The (partial) name this node should match on
  std::string prefix;
  // Optional sub-selectors
  std::vector<MyT> childNodes;
  // Callable matching f(Args...) -> Result. If this node is a leaf node, 
  // function is Either a target function, i.e. a result from the parse tree, 
  // or an Alias
  std::optional<TargetFunction> function;
  
  // Callable matching the target function signature. Can be used to indicate an
  // an alias and reroute the parse methods.
  class Alias
  {
  public:
    Result operator()(Args...) const { return Result(); }

    std::string query;
  };

  // Top-level parse function
  static std::optional<TargetFunction> 
    Parse(const std::vector<MyT>& nodes, const std::string& query)
  {
    const MyT root = { "", nodes };
    const std::optional<TargetFunction> targetFunction = root.Parse(query);

    if (targetFunction)
    {
      const Alias* alias = targetFunction->template target<Alias>();
      if (alias != nullptr)
      {
        // Result is an Alias, so start from the top
        return Parse(nodes, alias->query);
      }
    }
    
    // Result is either empty or not an Alias, so return it.
    return targetFunction;
  }

private:
  std::optional<TargetFunction> Parse(const std::string& query) const
  {
    if (!StartsWith(prefix, query))
      return {};

    // Assume child nodes are available and attempt to descend
    const std::string remainingQuery = ConsumePrefix(prefix, query);

    for (auto& node : childNodes)
    {
      const auto result = node.Parse(remainingQuery);
      if (result)
        return result;
    }

    return function;
  }
};

}  // namespace ChipSelect

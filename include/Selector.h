#pragma once

#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

bool StartsWith(const std::string& prefix, const std::string& query);
std::string ConsumePrefix(const std::string& prefix, const std::string& query);

template <typename Result, typename ...Args>
// Selects from functions which take Args and return Result
class Selector
{
  using TargetFunction = std::function<Result(Args...)>;

public:
  // Selector description
  // The (partial) name this node should match on
  std::string prefix;
  // Optional sub-selectors
  std::vector<Selector<Result, Args...>> childNodes;
  // Callable matching f(Args...) -> Result. If this node is a leaf node, 
  // function is Either a target function, i.e. a result from the parse tree, 
  // or an Alias
  std::optional<TargetFunction> function;
  
  // Callable matching the target function signature. Can be used to indicate an
  // an alias and reroute the parse methods.
  class Alias
  {
  public:
    Alias(const std::string& query) : query(query) { }
    Result operator()(Args...) const { return Result(); }
    std::string query;
  };

  // Top-level parse function
  static std::optional<TargetFunction> 
    Parse(const std::vector<Selector<Result, Args...>>& nodes, const std::string& query)
  {
    const Selector<Result, Args...> root = { "", nodes };
    auto targetFunction = root.Parse(query);

    if (!targetFunction)
    {
      return targetFunction;
    }
    else
    {
      const Alias* alias = targetFunction->template target<Alias>();
      if (alias == nullptr)
      {
        // Result does not resolve as an Alias, so it's a final result
        return targetFunction;
      }
      else
      {
        // Result resolves as an Alias, so start again
        return Parse(nodes, alias->query);
      }
    }
  }

private:
  std::optional<TargetFunction> Parse(const std::string& query) const
  {
    if (!StartsWith(prefix, query))
      return {};

    // Child nodes available, so descend
    const std::string remainingQuery = ConsumePrefix(prefix, query);

    for (auto& node : childNodes)
    {
      auto result = node.Parse(remainingQuery);
      if (result)
        return result;
    }

    return function;
  }
};

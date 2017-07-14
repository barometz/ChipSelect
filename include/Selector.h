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
  std::string prefix;
  std::vector<Selector<Result, Args...>> nodes;
  TargetFunction function;

  static std::optional<TargetFunction> 
    Parse(const std::vector<Selector<Result, Args...>>& nodes, const std::string& deviceName)
  {
    const Selector<Result, Args...> root = { "", nodes };
    return root.Parse(root, deviceName);
  }

  class Alias
  {
  public:
    Alias(const std::string& deviceName) : deviceName(deviceName) { }
    Result operator()(Args...) const { return Result(); }
    std::string deviceName;
  };

private:
  std::optional<TargetFunction> 
    Parse(const Selector<Result, Args...>& root, const std::string& deviceName) const
  {
    if (!StartsWith(prefix, deviceName))
      return {};

    if (nodes.empty())
    {
      if (function == nullptr)
        return {};
      else if (function.target<Alias>() != nullptr)
        return root.Parse(root, function.target<Alias>()->deviceName);
      else
        return function;
    }

    const std::string remainingDeviceName = ConsumePrefix(prefix, deviceName);

    for (auto& s : nodes)
    {
      auto result = s.Parse(root, remainingDeviceName);
      if (result)
        return result;
    }

    return {};
  }
};

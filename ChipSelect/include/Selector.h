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
public:
  using TargetFunction = std::function<Result(Args...)>;
  using List = std::vector<Selector<Result, Args...>>;

  // Selector description
  std::string prefix;
  List selectors;
  TargetFunction function;
  std::string alias;

  static std::optional<TargetFunction> Parse(const List& selectors, const std::string& deviceName)
  {
    const Selector<Result, Args...> root = { "", selectors };
    return root.ParseIt(selectors, deviceName);
  }

  static Result Alias(Args...)
  {
    return Result();
  }

private:
  std::optional<TargetFunction> ParseIt(const List& root, const std::string& deviceName) const
  {
    if (!StartsWith(prefix, deviceName))
      return {};

    if (selectors.empty())
    {
      if (function == nullptr)
      {
        return {};
      }
      else if (function.target<Result(Args...)>() == Alias)
      {
        return Parse(root, alias);
      }
      else if (function)
      {
        return function;
      }
      else
      {
        return {};
      }
    }

    const std::string remainingDeviceName = ConsumePrefix(prefix, deviceName);
    std::optional<TargetFunction> result{};

    for (auto& s : selectors)
    {
      result = s.ParseIt(root, remainingDeviceName);
      if (result)
        break;
    }

    return result;
  }
};

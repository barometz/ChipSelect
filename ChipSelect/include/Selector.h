#pragma once

#include <functional>
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

  static TargetFunction Parse(const List& selectors, const std::string& deviceName)
  {
    const Selector<Result, Args...> root = { "", selectors };
    std::optional<TargetFunction> result = root.Parse(deviceName);
    return result.value_or(Dummy);
  }

private:
  std::optional<TargetFunction> Parse(const std::string& deviceName) const
  {
    if (!StartsWith(prefix, deviceName))
      return {};

    if (selectors.empty())
      return function;

    const std::string remainingDeviceName = ConsumePrefix(prefix, deviceName);
    std::optional<TargetFunction> result{};

    for (auto& s : selectors)
    {
      result = s.Parse(remainingDeviceName);
      if (result)
        break;
    }

    return result;
  }

  static Result Dummy(Args...)
  {
    return Result();
  }
};

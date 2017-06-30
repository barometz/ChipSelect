#pragma once

#include <functional>
#include <string>
#include <vector>

inline bool StartsWith(const std::string& prefix, const std::string& query)
{
  return (query.compare(0, prefix.length(), prefix) == 0);
}

inline std::string ConsumePrefix(const std::string& prefix, const std::string& query)
{
  if (StartsWith(prefix, query))
    return query.substr(prefix.length());
  else
    return query;
}

template <typename Result, typename ...CreateArgs>
class Selector
{
public:
  using Create = std::function<Result(CreateArgs...)>;

  // Selector description
  std::string prefix;
  std::vector<Selector<Result, CreateArgs...>> selectors;
  Create function;

  static Create Parse(const std::vector<Selector<Result, CreateArgs...>>& selectors, const std::string& deviceName)
  {
    for (auto& s : selectors)
    {
      if (!StartsWith(s.prefix, deviceName))
        continue;

      if (s.selectors.empty())
        return s.function;

      std::string remainingDeviceName = ConsumePrefix(s.prefix, deviceName);
      return Parse(s.selectors, remainingDeviceName);
    }

    return [](CreateArgs... args) -> Result { return Result(); };
  }
};

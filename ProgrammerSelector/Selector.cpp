#include "Selector.h"

bool StartsWith(const std::string& prefix, const std::string& query)
{
  return (query.compare(0, prefix.length(), prefix) == 0);
}

std::string ConsumePrefix(const std::string& prefix, const std::string& query)
{
  if (StartsWith(prefix, query))
    return query.substr(prefix.length());
  else
    return query;
}

Create Selector::Parse(const std::vector<Selector>& selectors, const std::string& deviceName)
{
  for (auto& s : selectors)
  {
    if (StartsWith(s.prefix, deviceName))
    {
      if (s.selectors.empty())
      {
        return s.function;
      }
      else
      {
        std::string remainingDeviceName = ConsumePrefix(s.prefix, deviceName);
        return Parse(s.selectors, remainingDeviceName);
      }
    }
  }

  return [](CreateArgs args) { return nullptr; };
}
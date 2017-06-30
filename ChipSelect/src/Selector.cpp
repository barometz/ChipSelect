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

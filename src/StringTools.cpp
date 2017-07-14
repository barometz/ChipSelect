#include "StringTools.h"

#include <stdexcept>

namespace ChipSelect
{

bool StartsWith(const std::string& prefix, const std::string& query)
{
  if (prefix.length() == 0)
    return true;

  if (prefix[0] == '?' && query.length() > 0)
  {
    // If the prefix starts with a wildcard "?", drop the first character from
    // prefix and query and start over
    return StartsWith(prefix.substr(1), query.substr(1));
  }

  return (query.compare(0, prefix.length(), prefix) == 0);
}

std::string ConsumePrefix(const std::string& prefix, const std::string& query)
{
  if (StartsWith(prefix, query))
    return query.substr(prefix.length());
  else
    throw std::invalid_argument(query + " does not start with prefix " + prefix);
}

}  // namespace ChipSelect

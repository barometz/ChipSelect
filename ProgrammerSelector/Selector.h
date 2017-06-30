#pragma once

#include <functional>
#include <string>
#include <vector>

class CProgrammer;

typedef std::function<CProgrammer*(int)> Create;

class Selector
{
public:
  // Selector description
  std::string prefix;
  std::vector<Selector> selectors;
  Create function;

  Create Parse(const std::string& deviceName) const;
};


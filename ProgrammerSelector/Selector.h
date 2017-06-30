#pragma once

#include <functional>
#include <string>
#include <vector>

class CProgrammer;
class ISwd;
class IReport;

struct CreateArgs
{
  ISwd* Swd;
  IReport* Report;
};

typedef std::function<CProgrammer*(CreateArgs)> Create;

class Selector
{
public:
  // Selector description
  std::string prefix;
  std::vector<Selector> selectors;
  Create function;

  static Create Parse(const std::vector<Selector>& selectors, const std::string& deviceName);
};

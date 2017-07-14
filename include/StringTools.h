#pragma once

#include <string>

namespace ChipSelect
{

bool StartsWith(const std::string& prefix, const std::string& query);
std::string ConsumePrefix(const std::string& prefix, const std::string& query);

}  // namespace ChipSelect

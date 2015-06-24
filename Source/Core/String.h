#pragma once
#include <string>

// Can take multiple iterations of allocating buffers and attempting to format as it determines
std::string FormatString(const char* const formatString, ...);
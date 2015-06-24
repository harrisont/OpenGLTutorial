#include "String.h"
#include <memory>
#include <stdarg.h>

std::string FormatString(const char* const formatString, ...)
{
    va_list argptr;
    va_start(argptr, formatString);
    const auto formattedSize = 1 + _vscprintf(formatString, argptr);
    std::string result;
    result.resize(formattedSize);
    // This writes into the string's c_str() memory, which is unsafe, but works everywhere tested.
    // The alternative is to write to a separate character buffer, then construct a string from that buffer.
    // This alternative has the disadvantage of making a copy of the buffer.
    char* const resultBuffer = const_cast<char*>(result.c_str());
    vsnprintf_s(resultBuffer, formattedSize /*sizeOfBuffer*/, _TRUNCATE /*maxCount*/, formatString, argptr);
    return result;
}
#include "String.h"
#include <memory>
#include <stdarg.h>

std::string FormatString(const char* const formatString, ...)
{
    // Guess that the formatted string will need no more than two times as much as the length of the format string (plus one in case the size is 0).
    auto formattedSize = 1 + 2 * strlen(formatString);

    // If our guess for the formatted string size is too small, then it will use a larger guess the next iteration.
    for (;;)
    {
        const auto formattedString = std::make_unique<char[]>(formattedSize);

        va_list argptr;
        va_start(argptr, formatString);
        const auto numCharactersWritten = vsnprintf_s(&formattedString[0], formattedSize /*sizeOfBuffer*/, _TRUNCATE /*maxCount*/, formatString, argptr);
        va_end(argptr);

        if (numCharactersWritten == -1)
        {
            formattedSize *= 2;
        }
        else
        {
            return std::string(formattedString.get());
        }
    }
}
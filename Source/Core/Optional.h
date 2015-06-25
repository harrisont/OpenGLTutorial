// Temporary optional type until std::optional/std::experimental::optional is available.
// Use MakeOptional<T>, which creates an optional<T>.
// Implemented using std::unique_ptr, so it's not on the stack like it should eventually be.

#pragma once
#include <memory>

template<typename T>
using optional = std::unique_ptr<T>;

template<typename T, typename... Args>
inline auto MakeOptional(Args&&... args) -> decltype(std::make_unique<T>(std::forward<Args>(args)...))
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

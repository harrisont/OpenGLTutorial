#pragma once

// ArraySizeHelper takes a reference to an array of N Ts.
// It returns a reference to an array of N chars.
// ArraySizeHelper is never called, so we don't need to implement it.
// We just take the size of its return type.
//
// Referenced from http://stackoverflow.com/questions/1500363/compile-time-sizeof-array-without-using-a-macro
template <typename T, size_t N>
char(&ArraySizeHelper(T(&array)[N]))[N];

#define ARRAY_LENGTH(array) (sizeof(ArraySizeHelper(array)))

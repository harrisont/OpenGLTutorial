# C++ Compile Flags (All Configurations)
# -----------------------------------------------------------------------------
# /W4 level 4 warnings
# /WX treat warnings as errors
# /EHsc exception handling model (http://msdn.microsoft.com/en-us/library/1deeycx5.aspx)
# /GR- disable run-time type information
# /analyze enable static code analysis
set(CMAKE_CXX_FLAGS "/W4 /WX /EHsc /GR- /analyze")

# C++ Debug Compile Flags
# -----------------------------------------------------------------------------
# /MDd selects the runtime library (http://msdn.microsoft.com/en-us/library/2kzt1wy3.aspx)
# /ZI debug information format: generates PDB that supports Edit and Continue
# /Ob0 inline function expansion: disabled
# /Od optimizations disabled
# /RTC1 runtime checks
set(CMAKE_CXX_FLAGS_DEBUG "/MDd /ZI /Ob0 /Od /RTC1")

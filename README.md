# OpenGLTutorial
Following tutorial from http://learnopengl.com/.

## Dependencies
1. Python 3.4+
1. CMake 3.3+

## Setup
cmake must be on the PATH.

## Build
1. Generate: `python Source/BuildScripts/generate.py`
1. Build: one of
    * `python Source/BuildScripts/build.py`
    * Open the generated project with the appropriate generator (Visual Studio, XCode, etc.) and build it there.

## Run
`Build/GettingStarted/{config}/GettingStarted.exe`

For running in Visual Studio, set GettingStarted properties > Debugging > Working Directory to `$(TargetDir)`. 

include("${cmakeScriptsDir}/AddGlobbedFiles.cmake")

project(Core)

AddGlobbedFiles(core .)

add_library(${PROJECT_NAME} STATIC ${coreFiles})

include("${cmakeScriptsDir}/ConvertSlashes.cmake")

# Stores the files in the given directory into:
#   headers: "${outGlobbedFilesPrefixVar}Headers"
#   source: "${outGlobbedFilesPrefixVar}Sources"
#	combined: "${outGlobbedFilesPrefixVar}Files"
#
# directory can be either relative or absolute.
#
# Also creates a source group with the files.
# The source group's name is the directory.
#
# Example usage:
#   AddGlobbedFiles(foo dir)
#   add_executable(MyExecutable ${fooFiles})
function(AddGlobbedFiles outGlobbedFilesPrefixVar directory)
	#message("AddGlobbedFiles: outGlobbedFilesPrefixVar=${outGlobbedFilesPrefixVar}, directory=${directory}")

	file(GLOB headerFiles ${directory}/*.h ${directory}/*.hpp)
	file(GLOB sourceFiles ${directory}/*.cpp ${directory}/*.c  ${directory}/*.cc)

	# Ignore test sources.
	file(GLOB testFiles ${directory}/*.test.cpp ${directory}/*.test.c)
	if(testFiles)
		list(REMOVE_ITEM sourceFiles ${testFiles})
	endif()

	set(allFiles ${headerFiles} ${sourceFiles})

	set(headersVar ${outGlobbedFilesPrefixVar}Headers)
	set(sourcesVar ${outGlobbedFilesPrefixVar}Sources)
	set(filesVar ${outGlobbedFilesPrefixVar}Files)

	set(${headersVar} ${${headersVar}} ${headerFiles} PARENT_SCOPE)
	set(${sourcesVar} ${${sourcesVar}} ${sourceFiles} PARENT_SCOPE)
	set(${filesVar} ${${filesVar}} ${allFiles} PARENT_SCOPE)

	#message("AddGlobbedFiles: headerFiles=${headerFiles}")
	#message("AddGlobbedFiles: sourceFiles=${sourceFiles}")

	# Create a source group with the globbed files.  The name of the group is
	# the directory.
	get_filename_component(directoryAbsolute ${directory} ABSOLUTE)
	if(NOT ${directoryAbsolute} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
		ConvertToBackSlashes(sourceGroupName ${directory})
		#message("AddGlobbedFiles: sourceGroupName=${sourceGroupName}")
		source_group(${sourceGroupName} FILES ${allFiles})
	endif()
endfunction()
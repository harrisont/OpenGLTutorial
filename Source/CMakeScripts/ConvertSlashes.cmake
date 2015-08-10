function(ConvertToBackSlashes outVar input)
	string(REGEX REPLACE "/" "\\\\" replacedInput ${input})
	set(${outVar} ${replacedInput} PARENT_SCOPE)
endfunction()

function(ConvertToForwardSlashes outVar input)
	string(REGEX REPLACE "\\\\" "/" replacedInput ${input})
	set(${outVar} ${replacedInput} PARENT_SCOPE)
endfunction()
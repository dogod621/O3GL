add_subdirectory("Core")
add_subdirectory("Renders")

if(${O3GL_BUILD_DEMOS})
	add_subdirectory("Demos")
endif()
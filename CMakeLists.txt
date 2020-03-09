cmake_minimum_required(VERSION 3.2)
cmake_policy(VERSION 3.2)

# Create Project
project(O3GL)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Check Submodules are Cloned
if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/GLM)
  message(FATAL_ERROR "The GLM submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/GLEW)
  message(FATAL_ERROR "The GLEW submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

if(NOT IS_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/FreeGLUT)
  message(FATAL_ERROR "The FreeGLUT submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

# Setup GLM
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GLM/)

option(GLM_BUILD_SHARED_LIBS "Build the shared glm library" OFF)
option(GLM_BUILD_STATIC_LIBS "Build the static glm library" ON)

set(BUILD_SHARED_LIBS ${GLM_BUILD_SHARED_LIBS} CACHE BOOL " ")
set(BUILD_STATIC_LIBS ${GLM_BUILD_STATIC_LIBS} CACHE BOOL " ")
set(GLM_TEST_ENABLE OFF CACHE BOOL "Build glm unit tests")

add_subdirectory("GLM")
set(GLM_LIB_TARGETS)
if(${BUILD_SHARED_LIBS})
	if(TARGET glm_shared)
		list(APPEND GLM_LIB_TARGETS glm_shared)
	endif()
endif()
if(${BUILD_STATIC_LIBS})
	if(TARGET glm_static)
		list(APPEND GLM_LIB_TARGETS glm_static)
	endif()
endif()
set(GLM_EXE_TARGETS)
if(GLM_TEST_ENABLE)
	foreach(glm_test IN ITEMS "bug" "core" "ext" "gtc" "gtx" "perf")
		set(glm_test_root ${CMAKE_CURRENT_SOURCE_DIR}/GLM/test/${glm_test})
		string(LENGTH ${glm_test_root} glm_test_root_length)
		file(GLOB glm_test_sources ${glm_test_root}/*.cpp)
		foreach(glm_test_source IN LISTS glm_test_sources)
			string(LENGTH ${glm_test_source} glm_test_source_length)
			math(EXPR glm_test_name_begin "${glm_test_root_length}+1")
			math(EXPR glm_test_name_end "${glm_test_source_length}-${glm_test_name_begin}-4")
			string(SUBSTRING ${glm_test_source} ${glm_test_name_begin} ${glm_test_name_end} glm_test_name)
			if(TARGET test-${glm_test_name})
				list(APPEND GLM_EXE_TARGETS test-${glm_test_name})
			endif()
		endforeach()
	endforeach()
endif()
if(TARGET uninstall)
	set_target_properties(uninstall PROPERTIES FOLDER "GLM")
endif()
set_target_properties(${GLM_LIB_TARGETS} PROPERTIES FOLDER "GLM/LIB")
set_target_properties(${GLM_EXE_TARGETS} PROPERTIES FOLDER "GLM/EXE")

unset(BUILD_SHARED_LIBS CACHE)
unset(BUILD_STATIC_LIBS CACHE)

# Setup GLEW
set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GLEW/include/)

option(GLEW_BUILD_SHARED_LIBS "Build the shared glew library" OFF)
option(GLEW_BUILD_STATIC_LIBS "Build the static glew library" ON)
option(GLEW_BUILD_SINGLE_CONTEXT_LIBS "Build the single context glew library" ON)
option(GLEW_BUILD_MULTI_CONTEXT_LIBS "Build the multi context glew library" OFF)

set(glew-cmake_BUILD_SHARED ${GLEW_BUILD_SHARED_LIBS} CACHE BOOL " ")
set(glew-cmake_BUILD_STATIC ${GLEW_BUILD_STATIC_LIBS} CACHE BOOL " ")
set(glew-cmake_BUILD_SINGLE_CONTEXT ${GLEW_BUILD_SINGLE_CONTEXT_LIBS} CACHE BOOL " ")
set(glew-cmake_BUILD_MULTI_CONTEXT ${GLEW_BUILD_MULTI_CONTEXT_LIBS} CACHE BOOL " ")

add_subdirectory("GLEW")
set(GLEW_LIB_TARGETS)
if(${glew-cmake_BUILD_SHARED})
	add_definitions(-DGLEW_BUILD)
	if(${glew-cmake_BUILD_SINGLE_CONTEXT})
		if(TARGET libglew_shared)
			list(APPEND GLEW_LIB_TARGETS libglew_shared)
		endif()
	endif()
	if(${glew-cmake_BUILD_MULTI_CONTEXT})
		if(TARGET libglewmx_shared)
			list(APPEND GLEW_LIB_TARGETS libglewmx_shared)
		endif()
	endif()
endif()
if(${glew-cmake_BUILD_STATIC})
	add_definitions(-DGLEW_STATIC)
	if(${glew-cmake_BUILD_SINGLE_CONTEXT})
		if(TARGET libglew_static)
			list(APPEND GLEW_LIB_TARGETS libglew_static)
		endif()
	endif()
	if(${glew-cmake_BUILD_MULTI_CONTEXT})
		if(TARGET libglewmx_static)
			list(APPEND GLEW_LIB_TARGETS libglewmx_static)
		endif()
	endif()
endif()
set_target_properties(${GLEW_LIB_TARGETS} PROPERTIES FOLDER "GLEW/LIB")

unset(glew-cmake_BUILD_SHARED CACHE)
unset(glew-cmake_BUILD_STATIC CACHE)
unset(glew-cmake_BUILD_SINGLE_CONTEXT CACHE)
unset(glew-cmake_BUILD_MULTI_CONTEXT CACHE)

# Setup FreeGLUT
set(FREEGLUT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/FreeGLUT/include/)

IF(MSVC)
    option(FREEGLUT_INSTALL_PDB "Also install freeglut .pdb files" ON)
ELSE()
    set(FREEGLUT_INSTALL_PDB OFF)
ENDIF()

set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL " ")
set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL " ")
set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL " ")
set(INSTALL_PDB ${FREEGLUT_INSTALL_PDB} CACHE BOOL " ")

add_subdirectory("FreeGLUT")
set(FreeGLUT_LIB_TARGETS)
set(FreeGLUT_EXE_TARGETS)
if(${FREEGLUT_BUILD_SHARED_LIBS})
	if(TARGET freeglut)
		list(APPEND FreeGLUT_LIB_TARGETS freeglut)
	endif()
endif()
if(${FREEGLUT_BUILD_STATIC_LIBS})
	if(TARGET freeglut_static)
		list(APPEND FreeGLUT_LIB_TARGETS freeglut_static)
	endif()
endif()
if(${FREEGLUT_BUILD_DEMOS})
	foreach(freeglut_demo IN ITEMS "CallbackMaker" "Fractals" "Fractals_random" "Lorenz" "One" "Resizer" "multi-touch" "shapes" "smooth_opengl3" "subwin" "timer" "timer_callback" "spaceball")
		if(${FREEGLUT_BUILD_SHARED_LIBS})
			if(TARGET freeglut_demo)
				list(APPEND FreeGLUT_EXE_TARGETS freeglut_demo)
			endif()
		endif()
		if(${FREEGLUT_BUILD_STATIC_LIBS})
			if(TARGET ${freeglut_demo}_static)
				list(APPEND FreeGLUT_EXE_TARGETS ${freeglut_demo}_static)
			endif()
		endif()
	endforeach()
endif()
set_target_properties(${FreeGLUT_LIB_TARGETS} PROPERTIES FOLDER "FreeGLUT/LIB")
set_target_properties(${FreeGLUT_EXE_TARGETS} PROPERTIES FOLDER "FreeGLUT/EXE")

unset(INSTALL_PDB CACHE)

# Setup Include Dir
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${FREEGLUT_INCLUDE_DIR})

# Setup O3GL
set(O3GL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory("O3GL")
set_target_properties(O3GL_CORE PROPERTIES FOLDER "O3GL/LIB")
set_target_properties(O3GL_RENDERS PROPERTIES FOLDER "O3GL/LIB")

# Setup Demos
option(O3GL_BUILD_DEMOS "Build O3GL demos" ON)

function(AddDemo NAME)
	file(GLOB srcs	${CMAKE_CURRENT_SOURCE_DIR}/Demos/${NAME}/*.cpp)
	file(GLOB hpps	${CMAKE_CURRENT_SOURCE_DIR}/Demos/${NAME}/*.hpp)
	file(GLOB hdrs	${CMAKE_CURRENT_SOURCE_DIR}/Demos/${NAME}/*.h)
	set(TARGET_NAME ${NAME})
	add_executable(${TARGET_NAME} ${srcs} ${hpps} ${hdrs})
	set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "O3GL/EXE/Demos/")

	target_link_libraries(${TARGET_NAME} O3GL_CORE)
	target_link_libraries(${TARGET_NAME} O3GL_RENDERS)

	install(TARGETS ${TARGET_NAME}
			RUNTIME DESTINATION bin)
endfunction()

if(${O3GL_BUILD_DEMOS})
	AddDemo("Window")
	AddDemo("WindowEvents")
	AddDemo("Menue")
	AddDemo("DrawPrimitive")
	AddDemo("Framebuffer")
	AddDemo("MultipleRenderTargets")
	AddDemo("MultiLayeredRenderTarget")
endif()

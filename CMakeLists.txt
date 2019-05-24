cmake_minimum_required( VERSION 3.2 )

# Create Project
project( O3GL )

IF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
	set ( CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT OFF )
	set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME})
	#set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/../install/" CACHE PATH "${CMAKE_CURRENT_SOURCE_DIR}/../install/" FORCE)
ENDIF(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# 
if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/GLM")
  message(FATAL_ERROR "The GLM submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/GLEW")
  message(FATAL_ERROR "The GLEW submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

if(NOT IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FreeGLUT")
  message(FATAL_ERROR "The FreeGLUT submodule directory is missing! "
    "You probably did not clone the project with --recursive. It is possible to recover "
    "by running \"git submodule update --init --recursive\"")
endif()

# GLM
set(BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
set(BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)
add_subdirectory("GLM")
set(GLM_TARGETS)
if(${BUILD_SHARED_LIBS})
	list(APPEND GLM_TARGETS glm_shared)
endif()
if(${BUILD_STATIC_LIBS})
	list(APPEND GLM_TARGETS glm_static)
endif()
list(APPEND GLM_TARGETS 
	test-bug_ms_vec_static
	test-core_cpp_constexpr
	test-core_cpp_defaulted_ctor
	test-core_force_aligned_gentypes
	test-core_force_ctor_init
	test-core_force_explicit_ctor
	test-core_force_inline
	test-core_force_pure
	test-core_force_unrestricted_gentype
	test-core_force_xyzw_only
	test-core_type_aligned
	test-core_type_cast
	test-core_type_ctor
	test-core_type_int
	test-core_type_length
	test-core_type_mat2x2
	test-core_type_mat2x3
	test-core_type_mat2x4
	test-core_type_mat3x2
	test-core_type_mat3x3
	test-core_type_mat3x4
	test-core_type_mat4x2
	test-core_type_mat4x3
	test-core_type_mat4x4
	test-core_type_vec1
	test-core_type_vec2
	test-core_type_vec3
	test-core_type_vec4
	test-core_func_common
	test-core_func_exponential
	test-core_func_geometric
	test-core_func_integer
	test-core_func_integer_bit_count
	test-core_func_integer_find_lsb
	test-core_func_integer_find_msb
	test-core_func_matrix
	test-core_func_noise
	test-core_func_packing
	test-core_func_trigonometric
	test-core_func_vector_relational
	test-core_func_swizzle
	test-core_setup_force_cxx98
	test-core_setup_force_size_t_length
	test-core_setup_message
	test-core_setup_platform_unknown
	test-core_setup_precision
	test-ext_matrix_relational
	test-ext_matrix_transform
	test-ext_matrix_common
	test-ext_quaternion_common
	test-ext_quaternion_exponential
	test-ext_quaternion_geometric
	test-ext_quaternion_relational
	test-ext_quaternion_transform
	test-ext_quaternion_trigonometric
	test-ext_quaternion_type
	test-ext_scalar_common
	test-ext_scalar_constants
	test-ext_scalar_int_sized
	test-ext_scalar_uint_sized
	test-ext_scalar_ulp
	test-ext_scalar_relational
	test-ext_vec1
	test-ext_vector_bool1
	test-ext_vector_common
	test-ext_vector_iec559
	test-ext_vector_integer
	test-ext_vector_relational
	test-ext_vector_ulp
	test-gtc_bitfield
	test-gtc_color_space
	test-gtc_constants
	test-gtc_epsilon
	test-gtc_integer
	test-gtc_matrix_access
	test-gtc_matrix_integer
	test-gtc_matrix_inverse
	test-gtc_matrix_transform
	test-gtc_noise
	test-gtc_packing
	test-gtc_quaternion
	test-gtc_random
	test-gtc_round
	test-gtc_reciprocal
	test-gtc_type_aligned
	test-gtc_type_precision
	test-gtc_type_ptr
	test-gtc_ulp
	test-gtc_vec1
	test-gtx
	test-gtx_associated_min_max
	test-gtx_closest_point
	test-gtx_color_encoding
	test-gtx_color_space_YCoCg
	test-gtx_color_space
	test-gtx_common
	test-gtx_compatibility
	test-gtx_component_wise
	test-gtx_easing
	test-gtx_euler_angle
	test-gtx_extend
	test-gtx_extended_min_max
	test-gtx_exterior_product
	test-gtx_fast_exponential
	test-gtx_fast_square_root
	test-gtx_fast_trigonometry
	test-gtx_functions
	test-gtx_gradient_paint
	test-gtx_handed_coordinate_space
	test-gtx_integer
	test-gtx_intersect
	test-gtx_io
	test-gtx_load
	test-gtx_log_base
	test-gtx_matrix_cross_product
	test-gtx_matrix_decompose
	test-gtx_matrix_factorisation
	test-gtx_matrix_interpolation
	test-gtx_matrix_major_storage
	test-gtx_matrix_operation
	test-gtx_matrix_query
	test-gtx_matrix_transform_2d
	test-gtx_norm
	test-gtx_normal
	test-gtx_normalize_dot
	test-gtx_number_precision
	test-gtx_orthonormalize
	test-gtx_optimum_pow
	test-gtx_perpendicular
	test-gtx_polar_coordinates
	test-gtx_projection
	test-gtx_quaternion
	test-gtx_dual_quaternion
	test-gtx_range
	test-gtx_rotate_normalized_axis
	test-gtx_rotate_vector
	test-gtx_scalar_multiplication
	test-gtx_scalar_relational
	test-gtx_spline
	test-gtx_string_cast
	test-gtx_texture
	test-gtx_type_aligned
	test-gtx_type_trait
	test-gtx_vec_swizzle
	test-gtx_vector_angle
	test-gtx_vector_query
	test-gtx_wrap
	test-perf_matrix_div
	test-perf_matrix_inverse
	test-perf_matrix_mul
	test-perf_matrix_mul_vector
	test-perf_matrix_transpose
	test-perf_vector_mul_matrix)
	
set_target_properties(${GLM_TARGETS} PROPERTIES COMPILE_FLAGS "/wd4819" FOLDER "GLM")

# GLEW
set(glew-cmake_BUILD_SHARED OFF CACHE BOOL " " FORCE)
set(glew-cmake_BUILD_STATIC ON CACHE BOOL " " FORCE)
set(glew-cmake_BUILD_SINGLE_CONTEXT ON CACHE BOOL " " FORCE)
set(glew-cmake_BUILD_MULTI_CONTEXT OFF CACHE BOOL " " FORCE)
add_subdirectory("GLEW")
set(GLEW_TARGETS)
if(${glew-cmake_BUILD_SHARED})
	if(${glew-cmake_BUILD_SINGLE_CONTEXT})
		list(APPEND GLEW_TARGETS libglew_shared)
	endif()
	if(${glew-cmake_BUILD_MULTI_CONTEXT})
		list(APPEND GLEW_TARGETS libglewmx_shared)
	endif()
endif()
if(${glew-cmake_BUILD_STATIC})
	if(${glew-cmake_BUILD_SINGLE_CONTEXT})
		list(APPEND GLEW_TARGETS libglew_static)
	endif()
	if(${glew-cmake_BUILD_MULTI_CONTEXT})
		list(APPEND GLEW_TARGETS libglewmx_static)
	endif()
endif()

set_target_properties(${GLEW_TARGETS} PROPERTIES COMPILE_FLAGS "/wd4819" FOLDER "GLEW")

# FreeGLUT
set(FREEGLUT_BUILD_SHARED_LIBS OFF CACHE BOOL " " FORCE)
set(FREEGLUT_BUILD_STATIC_LIBS ON CACHE BOOL " " FORCE)
set(FREEGLUT_BUILD_DEMOS OFF CACHE BOOL " " FORCE)
add_subdirectory("FreeGLUT/freeglut/freeglut")
set(FreeGLUT_TARGETS)
if(${FREEGLUT_BUILD_SHARED_LIBS})
	list(APPEND FreeGLUT_TARGETS freeglut)
	set_property(TARGET freeglut PROPERTY FOLDER "FreeGLUT")
	if(${FREEGLUT_BUILD_DEMOS})
		list(APPEND FreeGLUT_TARGETS 
			CallbackMaker 
			Fractals
			Fractals_random
			Lorenz
			One
			Resizer
			multi-touch
			shapes
			smooth_opengl3
			subwin
			timer
			timer_callback)
		if(UNIX)
			list(APPEND FreeGLUT_TARGETS spaceball)
		endif()
	endif()
endif()
if(${FREEGLUT_BUILD_STATIC_LIBS})
	list(APPEND FreeGLUT_TARGETS freeglut_static)
	if(${FREEGLUT_BUILD_DEMOS})
		list(APPEND FreeGLUT_TARGETS 
			CallbackMaker_static 
			Fractals_static
			Fractals_random_static
			Lorenz_static
			One_static
			Resizer_static
			multi-touch_static
			shapes_static
			smooth_opengl3_static
			subwin_static
			timer_static
			timer_callback_static)
		if(UNIX)
			list(APPEND FreeGLUT_TARGETS spaceball_static)
		endif()
	endif()
endif()

set_target_properties(${FreeGLUT_TARGETS} PROPERTIES COMPILE_FLAGS "/wd4819" FOLDER "FreeGLUT")

# O3GL
add_subdirectory("O3GL")















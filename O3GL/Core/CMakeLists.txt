file(GLOB o3gl_core_srcs	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB o3gl_core_hpps	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB o3gl_core_hdrs	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

install(FILES ${o3gl_core_hpps} ${o3gl_core_hdrs} DESTINATION include/O3GL/Core/)

if(${O3GL_BUILD_SHARED_LIBS})
	add_library(o3gl_core SHARED ${o3gl_core_srcs} ${o3gl_core_hpps} ${o3gl_core_hdrs})
	set_target_properties(o3gl_core PROPERTIES FOLDER "O3GL/LIB")
	target_link_libraries(o3gl_core ${GLM_LIB_TARGETS})
	target_link_libraries(o3gl_core ${GLEW_LIB_TARGETS})
	target_link_libraries(o3gl_core ${FreeGLUT_LIB_TARGETS})
	install(TARGETS o3gl_core
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
endif()
if(${O3GL_BUILD_STATIC_LIBS})
	add_library(o3gl_core_static STATIC ${o3gl_core_srcs} ${o3gl_core_hpps} ${o3gl_core_hdrs})
	set_target_properties(o3gl_core_static PROPERTIES FOLDER "O3GL/LIB")
	target_link_libraries(o3gl_core_static ${GLM_LIB_TARGETS})
	target_link_libraries(o3gl_core_static ${GLEW_LIB_TARGETS})
	target_link_libraries(o3gl_core_static ${FreeGLUT_LIB_TARGETS})
	install(TARGETS o3gl_core_static
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
endif()

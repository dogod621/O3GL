file(GLOB o3gl_core_srcs	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB o3gl_core_hpps	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB o3gl_core_hdrs	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(O3GL_CORE STATIC ${o3gl_core_srcs} ${o3gl_core_hpps} ${o3gl_core_hdrs})

target_link_libraries(O3GL_CORE ${GLM_LIB_TARGETS})
target_link_libraries(O3GL_CORE ${GLEW_LIB_TARGETS})
target_link_libraries(O3GL_CORE ${FreeGLUT_LIB_TARGETS})

#Setup Install
install(FILES ${o3gl_core_hpps} ${o3gl_core_hdrs} DESTINATION include/O3GL/Core/)
install(TARGETS O3GL_CORE
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
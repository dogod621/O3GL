set(O3GL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/)

file(GLOB o3gl_srcs	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB o3gl_hpps	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB o3gl_hdrs	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(O3GL STATIC ${o3gl_srcs} ${o3gl_hpps} ${o3gl_hdrs})

target_link_libraries(O3GL ${GLM_LIB_TARGETS})
target_link_libraries(O3GL ${GLEW_LIB_TARGETS})
target_link_libraries(O3GL ${FreeGLUT_LIB_TARGETS})

#Setup Install
install(FILES ${o3gl_hpps} ${o3gl_hdrs} DESTINATION include/O3GL/)
install(TARGETS O3GL
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
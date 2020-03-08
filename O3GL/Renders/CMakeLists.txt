file(GLOB o3gl_renders_srcs	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB o3gl_renders_hpps	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB o3gl_renders_hdrs	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(O3GL_RENDERS STATIC ${o3gl_renders_srcs} ${o3gl_renders_hpps} ${o3gl_renders_hdrs})

target_link_libraries(O3GL_RENDERS O3GL_CORE)

#Setup Install
install(FILES ${o3gl_renders_hpps} ${o3gl_renders_hdrs} DESTINATION include/O3GL/Renders/)
install(TARGETS O3GL_RENDERS
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib)
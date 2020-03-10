file(GLOB o3gl_renders_srcs	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB o3gl_renders_hpps	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB o3gl_renders_hdrs	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

install(FILES ${o3gl_renders_hpps} ${o3gl_renders_hdrs} DESTINATION include/O3GL/Renders/)

if(${O3GL_BUILD_SHARED_LIBS})
	add_library(o3gl_renders SHARED ${o3gl_renders_srcs} ${o3gl_renders_hpps} ${o3gl_renders_hdrs})
	set_target_properties(o3gl_renders PROPERTIES FOLDER "O3GL/LIB")
	target_link_libraries(o3gl_renders o3gl_core)
	install(TARGETS o3gl_renders
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
endif()
if(${O3GL_BUILD_STATIC_LIBS})
	add_library(o3gl_renders_static STATIC ${o3gl_renders_srcs} ${o3gl_renders_hpps} ${o3gl_renders_hdrs})
	set_target_properties(o3gl_renders_static PROPERTIES FOLDER "O3GL/LIB")
	target_link_libraries(o3gl_renders_static o3gl_core_static)
	install(TARGETS o3gl_renders_static
			RUNTIME DESTINATION bin
			LIBRARY DESTINATION lib
			ARCHIVE DESTINATION lib)
endif()
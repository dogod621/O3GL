function(AddDemo NAME)
	file(GLOB srcs	${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/*.cpp)
	file(GLOB hpps	${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/*.hpp)
	file(GLOB hdrs	${CMAKE_CURRENT_SOURCE_DIR}/${NAME}/*.h)
	
	if(${O3GL_BUILD_SHARED_LIBS})
		set(TARGET_NAME ${NAME})
		add_executable(${TARGET_NAME} ${srcs} ${hpps} ${hdrs})
		set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "O3GL/EXE/Demos/")

		target_link_libraries(${TARGET_NAME} o3gl_core)
		target_link_libraries(${TARGET_NAME} o3gl_renders)

		install(TARGETS ${TARGET_NAME}
				RUNTIME DESTINATION bin)
	endif()
	if(${O3GL_BUILD_STATIC_LIBS})
		set(TARGET_NAME ${NAME}_static)
		add_executable(${TARGET_NAME} ${srcs} ${hpps} ${hdrs})
		set_target_properties(${TARGET_NAME} PROPERTIES FOLDER "O3GL/EXE/Demos/")

		target_link_libraries(${TARGET_NAME} o3gl_core_static)
		target_link_libraries(${TARGET_NAME} o3gl_renders_static)

		install(TARGETS ${TARGET_NAME}
				RUNTIME DESTINATION bin)
	endif()
	
endfunction()

AddDemo("Window")
AddDemo("WindowEvents")
AddDemo("Menue")
AddDemo("DrawPrimitive")
AddDemo("Framebuffer")
AddDemo("MultipleRenderTargets")
AddDemo("MultiLayeredRenderTarget")
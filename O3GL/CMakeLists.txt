cmake_minimum_required( VERSION 3.2 )

# 
file(GLOB o3gl_srcs	${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
file(GLOB o3gl_hpps	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp)
file(GLOB o3gl_hdrs	${CMAKE_CURRENT_SOURCE_DIR}/*.h)

add_library(O3GL STATIC ${o3gl_srcs} ${o3gl_hpps} ${o3gl_hdrs})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../GLM/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/include/)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../FreeGLUT/freeglut/freeglut/include/)

target_link_libraries(O3GL glm_static)
target_link_libraries(O3GL libglew_static)
target_link_libraries(O3GL freeglut_static)

# Install
install(FILES ${o3gl_hpps} ${o3gl_hdrs} DESTINATION include/O3GL/)
install(TARGETS O3GL
		RUNTIME DESTINATION bin/O3GL
		LIBRARY DESTINATION lib/O3GL
		ARCHIVE DESTINATION lib/O3GL)


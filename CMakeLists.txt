cmake_minimum_required(VERSION 3.7.2)
project(simple-physics2d VERSION 0.1.0)

include(CTest)
enable_testing()

# add executables
add_subdirectory(src)
add_executable(simple-physics2d ${EXE_SOURCE})

# add libraries
add_subdirectory(lib)
set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	glm
	GLAD_LIBRARY # not in ${}, because it is not a variable!
)

include_directories(
	lib/glfw-3.3.6/include/GLFW
	lib/glad/include/glad
	lib/glad/include/KHR
	lib/glm-0.9.9.8/glm
	${MODULES}
)

target_link_libraries(simple-physics2d ${ALL_LIBS})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

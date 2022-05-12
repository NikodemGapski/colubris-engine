

add_subdirectory(glfw-3.3.6)
add_subdirectory(glad)
add_subdirectory(glm-0.9.9.8)

include_directories(
	glfw-3.3.6/include/GLFW/
	glad/include/glad/
	glad/include/KHR/
	glm-0.9.9.8/glm/
)

# set GLFW library variable
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	# -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
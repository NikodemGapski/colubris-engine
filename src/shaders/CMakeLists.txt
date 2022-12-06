set(SHADER_SOURCE
	${CMAKE_CURRENT_SOURCE_DIR}/shader.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/shader.cpp
	PARENT_SCOPE
)

# do this to copy the files into the binary as a resource
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mesh_shader.vs ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/mesh_shader.fs ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/text_shader.vs ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/text_shader.fs ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
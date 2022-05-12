find_path(GLAD_HEADER glad.h include/glad)
find_path(KHR_HEADER khrplatform.h include/KHR)
include_directories(
	${GLAD_HEADER}
	${KHR_HEADER}
)
add_library(GLAD_LIBRARY src/glad.c)
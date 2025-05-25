

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})


add_subdirectory(glfw)
add_subdirectory(glm)
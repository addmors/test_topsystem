project( test_topsystem )

find_package( OpenGL REQUIRED )

FILE(GLOB_RECURSE headers "*.h")
FILE(GLOB_RECURSE sources "*.cpp")
FILE(GLOB_RECURSE shaders "*.vs" "*.geom" "*.frag")

add_executable( test_topsystem ${headers} ${sources} ${shaders})
set_target_properties(test_topsystem PROPERTIES FOLDER "test_topsystem")

GroupSourcesByFolder(test_topsystem)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR})
add_custom_command(
         TARGET test_topsystem POST_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy_directory              
             ${CMAKE_CURRENT_SOURCE_DIR}/shaders ${CMAKE_BINARY_DIR}/bin/shaders
         COMMENT "Copying shaders" VERBATIM
         )

set_property(TARGET test_topsystem PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

set_target_properties( test_topsystem
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

target_link_libraries( test_topsystem PRIVATE ${OPENGL_LIBRARIES} glfw glm glew)
target_include_directories(test_topsystem PRIVATE ${GLEW_ROOT}/include ${OPENGL_INCLUDE_DIRS})
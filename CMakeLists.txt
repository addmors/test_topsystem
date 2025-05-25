cmake_minimum_required( VERSION 3.5 )
set(CMAKE_CXX_STANDARD 20)

project(test)

function(GroupSourcesByFolder target) 
  set(SOURCE_GROUP_DELIMITER "/")
  set(last_dir "")
  set(files "")

  get_target_property(sources ${target} SOURCES)
  foreach(file ${sources})                                            
    file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" ${file}) 
    get_filename_component(dir "${relative_file}" PATH)               
    if(NOT "${dir}" STREQUAL "${last_dir}")
      if(files)
        source_group("${last_dir}" FILES ${files})
        message(${files})
      endif()
      set(files "")
    endif()
    set(files ${files} ${file})
    set(last_dir "${dir}")
  endforeach()

  if(files)
    source_group("${last_dir}" FILES ${files})
  endif()
endfunction()

add_subdirectory(submodules)

set(GLEW_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/submodules/glew)

add_library(glew STATIC IMPORTED)
set_target_properties(glew PROPERTIES
    IMPORTED_LOCATION "${GLEW_ROOT}/lib/Release/x64/glew32s.lib"
    INTERFACE_INCLUDE_DIRECTORIES "${GLEW_ROOT}/include"
)

add_subdirectory(src)

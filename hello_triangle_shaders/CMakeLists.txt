cmake_minimum_required(VERSION 3.6)   # CMake version check
project(antons_tutorials)               # Create project "simple_example"

set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

set(SOURCE_FILES hello_triangle.cpp)
add_executable(hello_triangle ${SOURCE_FILES})

#OPENGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(hello_triangle ${OPENGL_gl_LIBRARY})

#GLFW
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})
target_link_libraries(hello_triangle ${GLFW_LIBRARIES})

#GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(hello_triangle ${GLEW_LIBRARIES})
  endif()

  #GLM
  include_directories(hello_triangle ${GLM_INCLUDE_DIRS})
 






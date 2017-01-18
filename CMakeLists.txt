cmake_minimum_required(VERSION 3.6.2)
project(P2D)

# -std=c++14
set(CMAKE_CXX_STANDARD 14)

# Load headers
include_directories("include")

# Load sources
file(GLOB SOURCES "src/*.cpp")

# GLEW
find_package(glew REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})
  link_libraries(${GLEW_LIBRARIES})
endif()

# GLFW3
find_package(glfw3 3.2 REQUIRED)
if (GLFW3_FOUND)
  include_directories(${GLFW3_INCLUDE_DIRS})
  link_libraries(${GLFW3_LIBRARIES})
endif()

# BOOST
find_package(BOOST REQUIRED)
if (BOOST_FOUND)
  include_directories(${BOOST_INCLUDE_DIRS})
  link_libraries(${BOOST_LIBRARIES})
endif()

# OPENGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
  link_libraries(${OPENGL_LIBRARIES})
endif()

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} glfw)

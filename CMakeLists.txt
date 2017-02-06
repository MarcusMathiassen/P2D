cmake_minimum_required(VERSION 3.6.2)
project(P2D)

# Compiler flags
set(CMAKE_CXX_STANDARD 14)


# SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_BUILD_TYPE DEBUG)

SET(CMAKE_CXX_FLAGS_DEBUG)
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(CMAKE_CXX_FLAGS "-Wall")

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
  include_directories(${GLFW3_INCLUDES})
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

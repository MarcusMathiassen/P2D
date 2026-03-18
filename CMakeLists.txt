cmake_minimum_required(VERSION 3.6.2)
project(P2D)

# Compiler flags
set(CMAKE_CXX_STANDARD 14)


# SET(CMAKE_BUILD_TYPE DEBUG)
SET(CMAKE_BUILD_TYPE RELEASE)

SET(CMAKE_CXX_FLAGS_DEBUG)
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

SET(CMAKE_CXX_FLAGS "-Wall")
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)
add_definitions(-DGL_SILENCE_DEPRECATION)

# Load headers
include_directories("include")
include_directories("/opt/homebrew/include")

# Load sources
file(GLOB SOURCES "src/*.cpp")

# GLEW
find_package(GLEW REQUIRED)
if (GLEW_FOUND)
  include_directories(${GLEW_INCLUDE_DIRS})
endif()

# GLFW3
find_package(glfw3 3.2 REQUIRED)
if (GLFW3_FOUND)
  include_directories(${GLFW3_INCLUDES})
endif()

# BOOST
find_package(Boost REQUIRED)
if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# OPENGL
find_package(OpenGL REQUIRED)
if (OPENGL_FOUND)
  include_directories(${OPENGL_INCLUDE_DIRS})
endif()

# GLM
find_package(glm REQUIRED)

add_executable(${PROJECT_NAME} ${SOURCES})

# Prefer modern target link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    GLEW::glew
    glfw
    Boost::boost
    OpenGL::GL
    glm::glm
)

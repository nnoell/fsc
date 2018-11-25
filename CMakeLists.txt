# CMake
cmake_minimum_required (VERSION 3.8)

# Compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

# Dependencies
find_package(OpenGL)

# Variables
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(MICRO_VERSION 0)

# Definitions
add_definitions(-DFSC_VERSION="${MAJOR_VERSION}.${MINOR_VERSION}.${MICRO_VERSION}")

# Directories
set(FSCOUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FSCOUTPUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FSCOUTPUT_DIR})
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_FREETYPE_DIR ${CMAKE_SOURCE_DIR}/include/freetype)
set(LIBGLAD_DIR ${CMAKE_SOURCE_DIR}/src/libglad)
set(FSC_DIR ${CMAKE_SOURCE_DIR}/src/fsc)
set(FONT_DIR ${CMAKE_SOURCE_DIR}/src/font)

# Files
file(GLOB_RECURSE LIBGLAD_SOURCES ${LIBGLAD_DIR}/*.c)
file(GLOB_RECURSE FSC_SOURCES ${FSC_DIR}/*.cpp)
file(GLOB_RECURSE FONT_SOURCES ${FONT_DIR}/*.cpp)

# Libglad target
add_library(libglad STATIC ${LIBGLAD_SOURCES})
target_include_directories(libglad PUBLIC ${INCLUDE_DIR})
target_link_libraries(libglad)

# FSC target
add_executable(fsc ${FSC_SOURCES})
target_include_directories(fsc PUBLIC ${INCLUDE_DIR} ${INCLUDE_FREETYPE_DIR})
target_link_libraries(fsc libglad ${OPENGL_gl_LIBRARY} ${CMAKE_SOURCE_DIR}/lib/glfw/glfw3.lib ${CMAKE_SOURCE_DIR}/lib/freetype/freetype.lib)
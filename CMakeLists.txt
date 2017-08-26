cmake_minimum_required (VERSION 3.0)
project (CyberEngine)

#Output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CyberEngine_SOURCE_DIR}/Games)

#C++11
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
        message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

#PkgConfig
include(FindPkgConfig)

#SDL2
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

#CyberEngine
include_directories(${CyberEngine_SOURCE_DIR}/include)
file(GLOB_RECURSE CyberEngine_source_files src/*)
add_library(CyberEngine STATIC ${CyberEngine_source_files})
TARGET_LINK_LIBRARIES(CyberEngine
            ${SDL2_LIBRARIES} 
            ${OPENGL_LIBRARIES}
)

#Tetris
file(GLOB_RECURSE tetris_source_files Tetris/*)
add_executable(Tetris ${tetris_source_files})
TARGET_LINK_LIBRARIES(Tetris
            CyberEngine
)

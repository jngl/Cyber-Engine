cmake_minimum_required (VERSION 3.0)
project (CyberEngine)

include(FindPkgConfig)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CyberEngine_SOURCE_DIR}/Game)
set(CMAKE_CXX_STANDARD 17)

#CyberBase
add_subdirectory("ext/CyberBase")

#Libs
pkg_search_module(SDL2 REQUIRED sdl2)
find_package(OpenGL REQUIRED)

#GameEngine
file(GLOB_RECURSE GE_source_files src/*)
file(GLOB_RECURSE ext_source_files ext/src/*)

add_executable(GameEngine ${GE_source_files} ${ext_source_files})
TARGET_LINK_LIBRARIES(GameEngine
            ${SDL2_LIBRARIES} 
            ${OPENGL_LIBRARIES}
            ${CMAKE_DL_LIBS}
            CyberBase
)
target_include_directories(GameEngine PUBLIC 
            "${CyberEngine_SOURCE_DIR}/include"
            "${CyberEngine_SOURCE_DIR}/ext/include"
            ${SDL2_INCLUDE_DIRS}
            ${OpenGL_INCLUDE_DIRS}
)

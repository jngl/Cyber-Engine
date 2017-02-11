cmake_minimum_required (VERSION 3.0)
project (CyberEngine)

# Use our modified FindSDL2* modules
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CyberEngine_SOURCE_DIR}/cmake")

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

#SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

#SDL2_Image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

#OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -DGL_GLEXT_PROTOTYPES")

#GLM
find_package(glm REQUIRED)
include_directories(${GLM_INCLUDE_DIRS})

#OpenMP
find_package(OpenMP REQUIRED)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")

#Engine
include_directories(src/)

file(GLOB_RECURSE CyberEngine_source_files src/*)
add_library(CyberEngine ${CyberEngine_source_files})
TARGET_LINK_LIBRARIES(CyberEngine 
            ${SDL2_LIBRARY}  
            ${SDL2_IMAGE_LIBRARY}
            ${OPENGL_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${CMAKE_DL_LIBS}
)

#Boxel
file(GLOB_RECURSE Boxel_source_files Boxel/*)
add_executable(Boxel ${Boxel_source_files})
TARGET_LINK_LIBRARIES(Boxel
            CyberEngine
)

#Match
file(GLOB_RECURSE Match_source_files Match/*)
add_executable(Match ${Match_source_files})
TARGET_LINK_LIBRARIES(Match
            CyberEngine
)

#Voxel
file(GLOB_RECURSE Voxel_source_files Voxel/*)
add_executable(Voxel ${Voxel_source_files})
TARGET_LINK_LIBRARIES(Voxel
            CyberEngine
)

#Test 
file(GLOB_RECURSE Test_source_files test/*)
add_executable(Test ${Test_source_files})
TARGET_LINK_LIBRARIES(Test
            CyberEngine
)

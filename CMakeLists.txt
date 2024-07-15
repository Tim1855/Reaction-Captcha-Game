#set minimum version (fetch_content available since 3.11)
cmake_minimum_required(VERSION 3.11)

#set project nameproject(Reaction-Captcha-Game VERSION 0.0.1 LANGUAGES CXX)
project(Reaction-Captcha-Game)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# fetch tests
#include(FetchContent)
#FetchContent_Declare(
#    googletest
#    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
#)

# Detect the operating system
if(UNIX)
    message(STATUS "Compiling on Linux")
    add_definitions(-DOS_LINUX)
elseif(WIN32)
    message(STATUS "Compiling on Window")
    add_definitions(-DOS_WINDOWS)
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    #set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    #FetchContent_MakeAvailable(googletest)
elseif(APPLE)
    message(STATUS "Compiling on macOS")
    add_definitions(-DOS_MAC)
endif()


#enable_testing()
#add_subdirectory(test)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

#set variable executable
set(executable "Reaction-Captcha-Game")

# Define a variable for the source directory
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Gather all source files in the src directory
file(GLOB_RECURSE LibSources ${SRC_DIR}/*.cpp)

# list all the gathered files
message("LibSources: ${LibSources}")

# defines a static library and adds the include folder
add_library(GameLib STATIC ${LibSources})

# set the linker language for the library to c++
set_target_properties(GameLib PROPERTIES LINKER_LANGUAGE CXX)

# adds the execution file to the executable
add_executable(${executable} src/test_gm.cpp)

# sets the linker language for the executable
set_target_properties(${executable} PROPERTIES LINKER_LANGUAGE CXX)

# sets the include directory relativ to the project directory
target_include_directories(GameLib PUBLIC "${CMAKE_SOURCE_DIR}/inc/")
target_include_directories(${executable} PUBLIC "${CMAKE_SOURCE_DIR}/inc/")

# links the library "GameLib" with the executable
target_link_libraries(${executable} PRIVATE GameLib)

# links the opencv library with executable
target_link_libraries(${executable} PRIVATE ${OpenCV_LIBS})

# Define the current source directory as a macro
add_compile_definitions(SOURCE_DIR="${CMAKE_SOURCE_DIR}")
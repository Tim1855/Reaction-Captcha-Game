#set minimum version (fetch_content available since 3.11)
cmake_minimum_required(VERSION 3.11)

set(This gameTest)

# Define a variable for the test directory
set(TEST_DIR ${CMAKE_SOURCE_DIR}/test)

# Gather all source files in the src directory
file(GLOB_RECURSE Sources ${TEST_DIR}/*.cpp)

# list all the gathered files
message("Sources: ${Sources}")

add_executable(${This} ${Sources})

target_link_libraries(${This}
  gtest_main
  Reaction-Captcha-Game
)

add_test(
  NAME ${This}
  COMMAND ${This}
)
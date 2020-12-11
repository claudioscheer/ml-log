cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(ml-log)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(ml-log src/main.cpp)
target_link_libraries(ml-log cpp_redis pthread tacopie)

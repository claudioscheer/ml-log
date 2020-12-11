cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)
project(ml-log)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Drogon CONFIG REQUIRED)

add_executable(ml-log src/ml_log/main.cpp)
target_link_libraries(ml-log cpp_redis pthread tacopie)

add_executable(web-server src/web_server/main.cpp)
target_link_libraries(web-server cpp_redis pthread tacopie Drogon::Drogon)

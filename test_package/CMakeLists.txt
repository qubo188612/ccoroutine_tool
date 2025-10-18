cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(ccoroutine_tool CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example ccoroutine_tool::ccoroutine_tool)

cmake_minimum_required(VERSION 3.16)
project(itch50-parser CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(itch_parser src/main.cpp)

# warnings on from day one - they catch real bugs in byte-twiddling code
target_compile_options(itch_parser PRIVATE -Wall -Wextra)

cmake_minimum_required(VERSION 3.15)
project(Algorithm)

set(CMAKE_CXX_STANDARD 11)

#add_compile_options("-fsanitize=address")
#link_libraries("-fsanitize=address")

include_directories(include)
link_directories(lib)

link_libraries(fmt)

add_executable(Algorithm sort.cpp)
cmake_minimum_required(VERSION 3.15)

project(TakeBus)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

aux_source_directory(source SRC)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fexec-charset=GBK") #使用GBK编码

set(CMAKE_EXE_LINKER_FLAGS -static) #静态编译

#add_executable(TakeBus ${SRC} resources/icon.rc) #添加图标

add_executable(main ${SRC})

#ADD_EXECUTABLE(main include/model.h include/map.h include/menu.h source/map.cpp source/menu.cpp include/search.h source/search.cpp)
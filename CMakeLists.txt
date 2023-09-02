cmake_minimum_required(VERSION 3.17)
project(osgb_master)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)       #设置可执行文件的输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(dependencies/rapidjson)
add_subdirectory(dependencies/glfw-master)

include_directories(include)

file(GLOB SOURCES "src/*.cpp"
        "src/Tileset/*.cpp"
        )

add_library(osg SHARED ${SOURCES})
target_link_libraries(osg rapidjson )#将多目录下的hello库和world库链接上可执行文件helloworld.o


add_subdirectory(excample)

add_executable(osgb_master main.cpp)
add_executable(dome dome.cpp)
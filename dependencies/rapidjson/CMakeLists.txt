cmake_minimum_required(VERSION 3.5)
project(rapidjson)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -fPIC -w")#设置输出编码

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)       #设置可执行文件的输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)           #设置库文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_INSTALL_PREFIX "D:/install")

include_directories(include)
file(GLOB_RECURSE HEADER "include/*.h")
add_library(rapidjson INTERFACE)
target_include_directories(rapidjson INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

set_property(TARGET rapidjson PROPERTY EXPORT_NAME rapidjson)

install(TARGETS rapidjson
        EXPORT rapidjson-targets
        PUBLIC_HEADER DESTINATION include
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(EXPORT rapidjson-targets
        FILE rapidjson-config.cmake
        DESTINATION lib/cmake/rapidjson)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include)

add_executable(iostrimg main.cpp)
target_link_libraries(iostrimg rapidjson)

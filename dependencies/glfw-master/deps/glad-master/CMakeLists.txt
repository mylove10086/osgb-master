cmake_minimum_required(VERSION 3.4...3.20 FATAL_ERROR)

project(glad VERSION 3.4.0 LANGUAGES C)

set(GLAD_GL "include/glad/glad.h"
        include/KHR/khrplatform.h)
include_directories(include)
add_library(glad SHARED
        ${GLAD_GL}
        src/glad.c
        )
target_include_directories(glad PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)
install(TARGETS glad
        EXPORT gladTargets
        PUBLIC_HEADER DESTINATION glad
        RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")

install(EXPORT gladTargets
        FILE glad-config.cmake
        DESTINATION lib/cmake/glad)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include)
#add_executable(glads main.c)
#target_link_libraries(glads glad)#将多目录下的hello库和world库链接上可执行文件helloworld.o






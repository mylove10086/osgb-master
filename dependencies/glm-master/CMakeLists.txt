cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
cmake_policy(VERSION 3.2)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)       #设置可执行文件的输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)           #设置库文件的输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(CMAKE_INSTALL_PREFIX "D:/install")

file(READ "glm/detail/setup.hpp" GLM_SETUP_FILE)
string(REGEX MATCH "#define[ ]+GLM_VERSION_MAJOR[ ]+([0-9]+)" _ ${GLM_SETUP_FILE})
set(GLM_VERSION_MAJOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+GLM_VERSION_MINOR[ ]+([0-9]+)" _ ${GLM_SETUP_FILE})
set(GLM_VERSION_MINOR "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+GLM_VERSION_PATCH[ ]+([0-9]+)" _ ${GLM_SETUP_FILE})
set(GLM_VERSION_PATCH "${CMAKE_MATCH_1}")
string(REGEX MATCH "#define[ ]+GLM_VERSION_REVISION[ ]+([0-9]+)" _ ${GLM_SETUP_FILE})
set(GLM_VERSION_REVISION "${CMAKE_MATCH_1}")

set(GLM_VERSION ${GLM_VERSION_MAJOR}.${GLM_VERSION_MINOR}.${GLM_VERSION_PATCH}.${GLM_VERSION_REVISION})
project(glm VERSION ${GLM_VERSION} LANGUAGES CXX)
#set(BUILD_SHARED_LIBS true)                 # default is OFF

#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(glm)

add_library(glm::glm ALIAS glm)
target_include_directories(glm PUBLIC INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
        $<INSTALL_INTERFACE:include>)
set_property(TARGET glm PROPERTY EXPORT_NAME glm)

#message(${CMAKE_SOURCE_DIR})
#message(${CMAKE_CURRENT_SOURCE_DIR})
#STREQUAL 用于比较字符串，相同返回 true 。
#if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
    #message(1 "asdf")
    include(CPack)
    install(DIRECTORY glm
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            PATTERN "CMakeLists.txt" EXCLUDE)
    install(EXPORT glm
            FILE glmConfig.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/glm NAMESPACE glm::)
    #[[install(TARGETS glm
            EXPORT glm-targets
            PUBLIC_HEADER DESTINATION glm
            ARCHIVE DESTINATION lib COMPONENT Development
            LIBRARY DESTINATION lib COMPONENT Runtime
            RUNTIME DESTINATION bin COMPONENT Runtime)
    install(EXPORT glm-targets
            FILE glm-config.cmake
            DESTINATION lib/cmake/glm)]]
    include(CMakePackageConfigHelpers)
    #导出版本文件
    write_basic_package_version_file("glmConfigVersion.cmake" COMPATIBILITY AnyNewerVersion)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/glmConfigVersion.cmake
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/glm)

    include(CTest)
#endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_CURRENT_SOURCE_DIR})
if (NOT TARGET uninstall)
    configure_file(cmake/cmake_uninstall.cmake.in
            cmake_uninstall.cmake IMMEDIATE @ONLY)
    add_custom_target(uninstall
            "${CMAKE_COMMAND}" -P
            "${CMAKE_BINARY_DIR}/cmake_uninstall.cmake")
endif()

#add_executable(viewer main.cpp)
#target_link_libraries(viewer glm)#将多目录下的hello库和world库链接上可执行文件helloworld.o


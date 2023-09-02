# Copyright (C) 2007-2012 LuaDist.
# Created by Peter Kapec, David Manura
# Redistribution and use of this file is allowed according to the terms of the MIT license.
# For details see the COPYRIGHT file distributed with LuaDist.
# Please note that the package source code is licensed under its own license.
cmake_minimum_required(VERSION 3.16)

project(libjpeg C)
#include(cmake/dist.cmake)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)       #设置可执行文件的输出目录
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)           #设置库文件的输出目录

# jconfig.h
include(CheckIncludeFile)
check_include_file(stddef.h HAVE_STDDEF_H)
check_include_file(stdlib.h HAVE_STDLIB_H)
configure_file(include/jconfig.h.cmake include/jconfig.h)

include_directories(include)
#message(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB HEADERS "include/*.h")
#[[set(HEADERS
        jerror.h jmorecfg.h jpeglib.h ${CMAKE_CURRENT_BINARY_DIR}/jconfig.h)]]

#file(GLOB SRC "include/*.c")
set(SRC include/jmemnobs.c
        include/jaricom.c
        include/jcapimin.c
        include/jcapistd.c
        include/jcarith.c
        include/jccoefct.c
        include/jccolor.c
        include/jcdctmgr.c
        include/jchuff.c
        include/jcinit.c
        include/jcmainct.c
        include/jcmarker.c
        include/jcmaster.c
        include/jcomapi.c
        include/jcparam.c
        include/jcprepct.c
        include/jcsample.c
        include/jctrans.c
        include/jdapimin.c
        include/jdapistd.c
        include/jdarith.c
        include/jdatadst.c
        include/jdatasrc.c
        include/jdcoefct.c
        include/jdcolor.c
        include/jddctmgr.c
        include/jdhuff.c
        include/jdinput.c
        include/jdmainct.c
        include/jdmarker.c
        include/jdmaster.c
        include/jdmerge.c
        include/jdpostct.c
        include/jdsample.c
        include/jdtrans.c
        include/jerror.c
        include/jfdctflt.c
        include/jfdctfst.c
        include/jfdctint.c
        include/jidctflt.c
        include/jidctfst.c
        include/jidctint.c
        include/jquant1.c
        include/jquant2.c
        include/jutils.c
        include/jmemmgr.c
        include/cderror.h
        include/cdjpeg.h
        include/jdct.h
        include/jinclude.h
        include/jmemsys.h
        include/jpegint.h
        include/jversion.h
        include/transupp.h)


#message(12 ${HEADERS})
add_library(jpeg SHARED ${HEADERS} ${SRC})


target_include_directories(jpeg INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

set_property(TARGET jpeg PROPERTY EXPORT_NAME jpeg)

install(TARGETS jpeg
        EXPORT jpeg-targets
        PUBLIC_HEADER DESTINATION include
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(EXPORT jpeg-targets
        FILE jpeg-config.cmake
        DESTINATION lib/cmake/jpeg)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
        DESTINATION include)


add_executable(jpegz dome/dome.c)
target_link_libraries(jpegz jpeg)

set(execu
        2.1context.cpp
        2.2readosgb.cpp
        2.3readtree.cpp
        )

foreach (item ${execu})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${item})
    add_executable(${FILE_NAME} ${item})
    target_link_libraries(${FILE_NAME} osg)

endforeach ()
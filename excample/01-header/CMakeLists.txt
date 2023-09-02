set(execu
        1.0header.cpp
        )

foreach (item ${execu})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${item})
    add_executable(${FILE_NAME} ${item})
endforeach ()
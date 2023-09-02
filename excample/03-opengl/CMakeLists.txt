set(execu
        3.0opengl.cpp
        3.1showosgb.cpp
        3.2showopengl.cpp
        )
set(COMMON_LIBS glfw rapidjson )#Boost::algorithm

foreach (item ${execu})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${item})
    add_executable(${FILE_NAME} ${item})
    target_link_libraries(${FILE_NAME} osg ${COMMON_LIBS})

endforeach ()

set(execu2
        3.3outglb.cpp
        3.4outb3dm.cpp
        )

foreach (item ${execu2})
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${item})
    add_executable(${FILE_NAME} ${item})
    target_link_libraries(${FILE_NAME} osg )

endforeach ()
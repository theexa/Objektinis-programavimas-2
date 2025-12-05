cmake_minimum_required(VERSION 3.10)

project(StudentSorter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(StudentSorter
    main.cpp
    mylib.cpp
    mylib.h
)
file(GLOB DATA_FILES "${CMAKE_SOURCE_DIR}/*.txt")

foreach(file ${DATA_FILES})
    add_custom_command(
        TARGET StudentSorter POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${file}
        ${CMAKE_CURRENT_BINARY_DIR}
    )
endforeach()


cmake_minimum_required(VERSION 3.5)

project(ServerProject LANGUAGES C CXX)

set(HEADER_FILES_CONT inc/content_type.h)
add_library(content_type src/content_type.c ${HEADER_FILES_CONT})
target_include_directories(content_type PRIVATE inc/)

set(HEADER_FILES_SOCKET inc/socket_tool.h)
add_library(socket_tool src/socket_tool.c ${HEADER_FILES_SOCKET})
target_include_directories(socket_tool PRIVATE inc/)

set(HEADER_FILES ${HEADER_FILES_CONT} ${HEADER_FILES_SOCKET})

add_executable(ServerProject src/main.c ${HEADER_FILES})
target_include_directories(ServerProject PRIVATE inc/)
target_link_libraries(ServerProject content_type socket_tool)
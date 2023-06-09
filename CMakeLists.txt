cmake_minimum_required(VERSION 3.5)

project(ServerProject LANGUAGES C CXX)

set(HEADER_FILES_FILE_TOOL inc/file_tool.h)
add_library(file_tool src/file_tool.c ${HEADER_FILES_FILE_TOOL})
target_include_directories(file_tool PRIVATE inc/)

set(HEADER_FILES_CONT inc/content_type.h)
add_library(content_type src/content_type.c ${HEADER_FILES_CONT})
target_include_directories(content_type PRIVATE inc/)

set(HEADER_FILES_CLIENT inc/client_tool.h)
add_library(client src/client_tool.c ${HEADER_FILES_CLIENT})
target_include_directories(client PRIVATE inc/)

set(HEADER_FILES_SOCKET inc/socket_tool.h)
add_library(socket_tool src/socket_tool.c ${HEADER_FILES_SOCKET})
target_include_directories(socket_tool PRIVATE inc/)

set(HEADER_FILES_HTTP inc/http_request.h inc/file_tool.h)
add_library(http_request src/http_request.c ${HEADER_FILES_HTTP})
target_include_directories(http_request PRIVATE inc/)

set(HEADER_FILES ${HEADER_FILES_CONT} ${HEADER_FILES_SOCKET} ${HEADER_FILES_CLIENT} ${HEADER_FILES_HTTP} ${HEADER_FILES_FILE_TOOL})

add_executable(ServerProject src/main.c ${HEADER_FILES})
target_include_directories(ServerProject PRIVATE inc/)
target_link_libraries(ServerProject content_type socket_tool client http_request file_tool)
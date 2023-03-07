cmake_minimum_required(VERSION 3.5)

project(ListingNetworkAdapters LANGUAGES C CXX)

set(HEADER_FILES inc/content_type.h)
add_library(content_type src/content_type.c ${HEADER_FILES})
target_include_directories(content_type PRIVATE inc/)

add_executable(ListingNetwork src/main.c ${HEADER_FILES})
target_include_directories(ListingNetwork PRIVATE inc/)
target_link_libraries(ListingNetwork content_type)
cmake_minimum_required(VERSION 3.10)

project(thread-context VERSION 1.0)

add_library(thread-context SHARED
    ${CMAKE_CURRENT_SOURCE_DIR}/src/thread-context.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set_target_properties(thread-context PROPERTIES
    PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/include/thread-context.h
)

install(TARGETS thread-context
    RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
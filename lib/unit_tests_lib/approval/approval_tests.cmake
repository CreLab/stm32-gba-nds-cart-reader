cmake_minimum_required(VERSION 3.25)

if (NOT TARGET ApprovalTests)
    set(LIB_NAME ApprovalTests)
    add_library(${LIB_NAME} INTERFACE)
    target_include_directories(${LIB_NAME} INTERFACE ${CMAKE_CURRENT_LIST_DIR})
    add_library(${LIB_NAME}::${LIB_NAME} ALIAS ${LIB_NAME})
endif ()

cmake_minimum_required(VERSION 3.25)

find_package(Catch2 3.3 QUIET GLOBAL)

set(CATCH_CONFIG_CONSOLE_WIDTH "400" CACHE STRING "Read doc/configuration.md for details")
if (${Catch2_FOUND})
    message(STATUS "Found installed version of Catch2 ${Catch2_VERSION}")
else ()
    set(catch_tag "v3.9.0")
    message(STATUS "No installed version of Catch2 found.")
    message(STATUS "Downloading Version ${catch_tag} ...")
    include(FetchContent)
    FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG ${catch_tag}
            GIT_PROGRESS TRUE
    )
    message(STATUS "Downloading Done")
    FetchContent_MakeAvailable(Catch2)
    list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
endif ()
include(CTest)
include(Catch)
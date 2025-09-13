cmake_minimum_required(VERSION 3.25)

function(add_unit_test name)

    if (NOT ENABLE_UNIT_TESTS)
        message("ENABLE_UNIT_TESTS is not active!!")
        return()
    endif ()

    set(options "NO_TEAMCITY")
    set(oneValueArgs OBJECT PREFIX LIBS)
    set(multiValueArgs SOURCES SOURCE_FILE MOCKING_OBJECTS)
    cmake_parse_arguments(ADD_UNIT_TEST "${options}" "${oneValueArgs}"
                          "${multiValueArgs}" ${ARGN})

    if (NOT ADD_UNIT_TEST_SOURCES)
        message(FATAL_ERROR "Missing SOURCES")
    endif ()

    if (ADD_UNIT_TEST_PREFIX)
        set(add_prefix PREFIX ${ADD_UNIT_TEST_PREFIX})
    endif ()

    add_executable(${name})
    target_link_libraries(${name} PRIVATE
                          Catch2::Catch2WithMain
                          ApprovalTests::ApprovalTests
                          ${ADD_UNIT_TEST_OBJECT}
                          ${ADD_UNIT_TEST_MOCKING_OBJECTS}
                          ${ADD_UNIT_TEST_LIBS}
                          )
    target_sources(${name} PRIVATE ${ADD_UNIT_TEST_SOURCES})
    target_sources(${name} PRIVATE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/approval_test_settings.cpp)
    target_link_options(${name} PRIVATE -Wl,--gc-sections)
    target_link_options(${name} PRIVATE --coverage)
    target_compile_features(${name} PRIVATE cxx_std_23)
    catch_discover_tests(${name} ${add_prefix})

    if (ADD_UNIT_TEST_OBJECT)
        if (TARGET ${ADD_UNIT_TEST_OBJECT})
            target_link_libraries(${name} PRIVATE ${ADD_UNIT_TEST_OBJECT})
            target_compile_options(${ADD_UNIT_TEST_OBJECT} PRIVATE --coverage)
            target_link_options(${ADD_UNIT_TEST_OBJECT} PRIVATE --coverage)
        else ()
            MESSAGE(FATAL_ERROR "OBJECT ${ADD_UNIT_TEST_OBJECT} is not a target")
        endif ()

    elseif (ADD_UNIT_TEST_SOURCE_FILE)
        message(STATUS "Add Source Files: ")

        foreach(test_file IN LISTS ADD_UNIT_TEST_SOURCE_FILE)
            if (EXISTS ${test_file})

                message(STATUS "${test_file}")

                target_sources(${name} PRIVATE ${test_file})
                get_source_file_property(compile_options_local ${test_file} COMPILE_OPTIONS)

                if (compile_options_local)
                    list(APPEND ${compile_options_local} --coverage)
                else ()
                    set(compile_options_local --coverage)
                endif ()

                set_source_files_properties(${test_file} PROPERTIES COMPILE_OPTIONS ${compile_options_local})

            else ()
                MESSAGE(FATAL_ERROR "SOURCE_FILE ${test_file} is not a file")
            endif ()
        endforeach()

        target_link_options(${name} PRIVATE --coverage )
    else ()
        target_compile_options(${name} PRIVATE --coverage)
        target_link_options(${name} PRIVATE --coverage)
    endif ()
endfunction()
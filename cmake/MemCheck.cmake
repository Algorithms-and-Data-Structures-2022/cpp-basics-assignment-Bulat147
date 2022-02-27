function(enable_memcheck)

    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        string(TOLOWER ${CMAKE_BUILD_TYPE} build_type)

        if (build_type STREQUAL "debug")
            message(STATUS "MemoryCheck: enabled")

            # See https://valgrind.org/docs/manual/manual.html
            add_compile_options(-g -fno-inline -fno-inline-small-functions)
        else (build_type STREQUAL "debug")
            message(FATAL_ERROR "MemoryCheck: disabled.\nReason: Expected debug build type, got ${CMAKE_BUILD_TYPE}.")
        endif (build_type STREQUAL "debug")

    else (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        message(AUTHOR_WARNING "Memcheck does not support '${CMAKE_CXX_COMPILER_ID}' compiler.")
    endif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

endfunction(enable_memcheck)
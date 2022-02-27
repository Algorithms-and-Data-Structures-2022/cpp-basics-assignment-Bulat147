# Catch2
if (NOT EXISTS "${PROJECT_SOURCE_DIR}/contrib/Catch2/CMakeLists.txt")
    message(FATAL_ERROR "submodule contrib/Catch2 is missing. To fix try run:
    git submodule update --init --recursive")
else ()
    option(CATCH_INSTALL_DOCS "Install docs" OFF)
    option(CATCH_BUILD_TESTING "Enable testing" OFF)
    option(CATCH_BUILD_EXAMPLES "Build examples" OFF)

    add_subdirectory(${PROJECT_SOURCE_DIR}/contrib/Catch2 ${CMAKE_CURRENT_BINARY_DIR}/Catch2)
endif ()
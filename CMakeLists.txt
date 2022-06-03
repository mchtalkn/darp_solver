# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMakeProject1")

# Add source to this project's executable.
add_executable (bftest "main.cpp")

# TODO: Add tests and install targets if needed.
set(CMAKE_CXX_FLAGS "-O3")

add_subdirectory("darp")
target_link_libraries(bftest darp)

target_include_directories(bftest PUBLIC
                          "${PROJECT_BINARY_DIR}"
                          "${PROJECT_SOURCE_DIR}/darp"
                          )
set_target_properties( bftest
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}"
)

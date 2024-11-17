cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(game VERSION 1.0)

option(ENABLE_CLANG_TIDY "Enable clang-tidy for static analysis" OFF)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

if(ENABLE_CLANG_TIDY)
    find_program(CLANG_TIDY_PROGRAM clang-tidy)
    if(CLANG_TIDY_PROGRAM)
        message(STATUS "Using clang-tidy: ${CLANG_TIDY_PROGRAM}")
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_PROGRAM};-header-filter=.*")
        set(USE_PCH OFF)
    else()
        message(WARNING "clang-tidy not found, ignoring ENABLE_CLANG_TIDY option.")
    endif()
else()
    set(USE_PCH ON)
endif()

set(LIBRARY_PATH "${CMAKE_SOURCE_DIR}/../raylib")
set(PCH_PATH "${CMAKE_SOURCE_DIR}/common")
set(PCH_HEADER "${PCH_PATH}/PCH.hpp")
set(SOURCE_PATH "${CMAKE_SOURCE_DIR}/source")

include_directories("${LIBRARY_PATH}")
include_directories("${PCH_PATH}")
file(GLOB_RECURSE SOURCE_FILES "${SOURCE_PATH}/*.cpp")

add_executable(game main.cpp "${SOURCE_FILES}")

target_include_directories(game PRIVATE "${CMAKE_SOURCE_DIR}/include")

if (USE_PCH)
    target_precompile_headers(game PRIVATE "${PCH_HEADER}")
endif()

target_link_libraries(game PRIVATE
    "${LIBRARY_PATH}/libraylib.a"
    "-framework CoreVideo"
    "-framework IOKit"
    "-framework Cocoa"
    "-framework GLUT"
    "-framework OpenGL"
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
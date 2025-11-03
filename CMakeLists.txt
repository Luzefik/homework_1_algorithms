cmake_minimum_required(VERSION 4.0)
project(homework_1)

set(CMAKE_CXX_STANDARD 17)

# Put the built executable into the project's bin/ directory (creates it under project root)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

add_executable(homework_1
        ${SRC_DIR}/main.cpp
        ${SRC_DIR}/file_utils.cpp
        ${SRC_DIR}/sorting.cpp
        ${SRC_DIR}/DataStructureV1.cpp
        ${SRC_DIR}/DataStructureV2.cpp
        ${SRC_DIR}/DataStructureV3.cpp
        ${SRC_DIR}/benchmark_runner.cpp
        ${SRC_DIR}/mem_utils.cpp)

add_executable(run_all
        ${SRC_DIR}/run_all.cpp
        ${SRC_DIR}/benchmark_runner.cpp
        ${SRC_DIR}/file_utils.cpp
        ${SRC_DIR}/DataStructureV1.cpp
        ${SRC_DIR}/DataStructureV2.cpp
        ${SRC_DIR}/DataStructureV3.cpp
        ${SRC_DIR}/mem_utils.cpp
        ${SRC_DIR}/sorting.cpp)
cmake_minimum_required(VERSION 3.16)
project(homework_1 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Place built executables into the project's bin/ directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(${INCLUDE_DIR})

set(SRC_COMMON
    ${SRC_DIR}/file_utils.cpp
    ${SRC_DIR}/sorting.cpp
    ${SRC_DIR}/DataStructureV1.cpp
    ${SRC_DIR}/DataStructureV2.cpp
    ${SRC_DIR}/DataStructureV3.cpp
    ${SRC_DIR}/benchmark_runner.cpp
    ${SRC_DIR}/mem_utils.cpp
)

add_executable(homework_1
    ${SRC_DIR}/main.cpp
    ${SRC_COMMON}
)

add_executable(run_all
    ${SRC_DIR}/run_all.cpp
    ${SRC_COMMON}
)

install(TARGETS homework_1 run_all
        RUNTIME DESTINATION bin)

install(DIRECTORY ${INCLUDE_DIR}/
        DESTINATION include/homework_1
        FILES_MATCHING PATTERN "*.h")

option(BUILD_TESTING "Build tests" OFF)

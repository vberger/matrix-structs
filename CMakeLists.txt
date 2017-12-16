cmake_minimum_required(VERSION 3.1)

project(matrix-structs CXX)

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -std=c++1z \
        -Wall \
        -Wextra \
        -Werror \
        -pipe \
        -pedantic \
        -Wunreachable-code")

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU")
        execute_process(COMMAND ${CMAKE_CXX_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)

        if (GCC_VERSION VERSION_GREATER 4.9)
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always" )
        endif()
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color=always" )
    endif()
endif()

file(DOWNLOAD
    "https://github.com/nlohmann/json/releases/download/v2.1.1/json.hpp" deps/json.hpp
    EXPECTED_MD5 "871e326cf493d17bce4578656759283d")

file(DOWNLOAD
    "https://github.com/mpark/variant/releases/download/v1.3.0/variant.hpp" deps/variant.hpp
    EXPECTED_MD5 "be0ce322cdd408e1b347b9f1d59ea67a")

include_directories(deps)
include_directories(include)

add_library(matrix_structs INTERFACE)
target_include_directories(matrix_structs INTERFACE
    include
    deps/json/src
    deps/variant/include/mpark)

if (BUILD_TESTS)
    enable_testing()

    file(COPY fixtures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    add_executable(identifiers tests/identifiers.cpp)
    target_link_libraries(identifiers ${CMAKE_PRJECT_NAME} ${GTEST_BOTH_LIBRARIES})

    add_executable(events tests/events.cpp)
    target_link_libraries(events ${CMAKE_PRJECT_NAME} ${GTEST_BOTH_LIBRARIES})

    add_executable(messages tests/messages.cpp)
    target_link_libraries(messages ${CMAKE_PRJECT_NAME} ${GTEST_BOTH_LIBRARIES})

    add_executable(responses tests/responses.cpp)
    target_link_libraries(responses ${CMAKE_PRJECT_NAME} ${GTEST_BOTH_LIBRARIES})

    add_test(MatrixIdentifiers identifiers)
    add_test(StateEvents events)
    add_test(RoomEvents messages)
    add_test(Responses responses)
endif()

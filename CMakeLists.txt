cmake_minimum_required(VERSION 3.1)

project(matrix_structs VERSION 0.1.0 LANGUAGES CXX)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_DOC "Build documentation" OFF)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

#
# Find doxygen & generate API documentation.
#
if(BUILD_DOC)
  include(Doxygen)
endif()

file(DOWNLOAD
       "https://github.com/nlohmann/json/releases/download/v3.1.2/json.hpp"
       ${PROJECT_SOURCE_DIR}/include/json.hpp
     EXPECTED_HASH
       SHA256=fbdfec4b4cf63b3b565d09f87e6c3c183bdd45c5be1864d3fcb338f6f02c1733)

file(DOWNLOAD
       "https://github.com/mpark/variant/releases/download/v1.3.0/variant.hpp"
       ${PROJECT_SOURCE_DIR}/include/variant.hpp
     EXPECTED_MD5 "be0ce322cdd408e1b347b9f1d59ea67a")

set(SRC
    src/events.cpp
    src/requests.cpp
    src/errors.cpp
    src/common.cpp
    src/events/aliases.cpp
    src/events/avatar.cpp
    src/events/canonical_alias.cpp
    src/events/common.cpp
    src/events/create.cpp
    src/events/encrypted.cpp
    src/events/encryption.cpp
    src/events/guest_access.cpp
    src/events/history_visibility.cpp
    src/events/join_rules.cpp
    src/events/member.cpp
    src/events/name.cpp
    src/events/pinned_events.cpp
    src/events/power_levels.cpp
    src/events/redaction.cpp
    src/events/tag.cpp
    src/events/topic.cpp
    src/events/messages/audio.cpp
    src/events/messages/emote.cpp
    src/events/messages/file.cpp
    src/events/messages/image.cpp
    src/events/messages/notice.cpp
    src/events/messages/text.cpp
    src/events/messages/video.cpp
    src/responses/common.cpp
    src/responses/create_room.cpp
    src/responses/crypto.cpp
    src/responses/login.cpp
    src/responses/register.cpp
    src/responses/empty.cpp
    src/responses/media.cpp
    src/responses/messages.cpp
    src/responses/notifications.cpp
    src/responses/profile.cpp
    src/responses/sync.cpp
    src/responses/version.cpp)

add_library(matrix_structs ${SRC})
if(NOT MSVC)
  target_compile_options(matrix_structs
                         PRIVATE
                         -Wall
                         -Wextra
                         -Werror
                         -Wunreachable-code
                         -fdiagnostics-color=always
                         -pipe
                         -pedantic)
endif()

target_include_directories(
  matrix_structs
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src)

#
# Installation & Target configuration.
#
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/MatrixStructs)

install(TARGETS matrix_structs
        EXPORT matrix_structs-targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

set_target_properties(matrix_structs PROPERTIES EXPORT_NAME MatrixStructs)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT matrix_structs-targets
               FILE
               MatrixStructsTargets.cmake
               NAMESPACE
               MatrixStructs::
               DESTINATION
               ${INSTALL_CONFIGDIR})

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${CMAKE_CURRENT_BINARY_DIR}/MatrixStructsConfigVersion.cmake
  VERSION
  ${PROJECT_VERSION}
  COMPATIBILITY
  AnyNewerVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/MatrixStructsConfig.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/MatrixStructsConfig.cmake
  INSTALL_DESTINATION
  ${INSTALL_CONFIGDIR})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/MatrixStructsConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/MatrixStructsConfigVersion.cmake
              DESTINATION
              ${INSTALL_CONFIGDIR})

export(EXPORT
       matrix_structs-targets
       FILE
       ${CMAKE_CURRENT_BINARY_DIR}/MatrixStructsTargets.cmake
       NAMESPACE
       MatrixStructs::)
export(PACKAGE MatrixStructs)

#
# Test configuration
#
if(BUILD_TESTS)
  enable_testing()

  file(COPY fixtures DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

  find_package(GTest)

  if(NOT GTest_FOUND)
    include(${CMAKE_SOURCE_DIR}/cmake/GoogleTest.cmake)
  endif()

  include_directories(${GTEST_INCLUDE_DIRS})

  add_executable(identifiers tests/identifiers.cpp)
  target_link_libraries(identifiers matrix_structs ${GTEST_BOTH_LIBRARIES})

  add_executable(events tests/events.cpp)
  target_link_libraries(events matrix_structs ${GTEST_BOTH_LIBRARIES})

  add_executable(messages tests/messages.cpp)
  target_link_libraries(messages matrix_structs ${GTEST_BOTH_LIBRARIES})

  add_executable(responses tests/responses.cpp)
  target_link_libraries(responses matrix_structs ${GTEST_BOTH_LIBRARIES})

  add_executable(requests tests/requests.cpp)
  target_link_libraries(requests matrix_structs ${GTEST_BOTH_LIBRARIES})

  add_executable(errors tests/errors.cpp)
  target_link_libraries(errors matrix_structs ${GTEST_BOTH_LIBRARIES})

  add_executable(crypto tests/crypto.cpp)
  target_link_libraries(crypto matrix_structs ${GTEST_BOTH_LIBRARIES})

  if(NOT GTest_FOUND)
    add_dependencies(identifiers GTest)
    add_dependencies(events GTest)
    add_dependencies(messages GTest)
    add_dependencies(responses GTest)
    add_dependencies(requests GTest)
    add_dependencies(errors GTest)
    add_dependencies(crypto GTest)
  endif()

  add_test(MatrixIdentifiers identifiers)
  add_test(MatrixErrors errors)
  add_test(CryptoStructs crypto)
  add_test(StateEvents events)
  add_test(RoomEvents messages)
  add_test(Responses responses)
  add_test(Requests requests)
endif()

set_property(TARGET matrix_structs PROPERTY SOVERSION ${PROJECT_VERSION})

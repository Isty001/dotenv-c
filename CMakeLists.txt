cmake_minimum_required(VERSION 3.12)
project(dotenv)

# Determine build type. Default to RELEASE
if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE RELEASE)
else()
    string(TOUPPER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE)
endif()
message(STATUS "Building dotenv-c ${CMAKE_BUILD_TYPE}")

# Config options
option(DOTENV_SHARED "Build shared library" ON)
option(DOTENV_STATIC "Build static library" ON)
option(DOTENV_TEST "Build tests" OFF)

# Compile options
if ("${CMAKE_BUILD_TYPE}" STREQUAL "DEBUG")
    set(DOTENV_COMPILE_OPTIONS -g -Wall -Wextra -ftrapv -Wshadow -Wundef -Wcast-align -Wunreachable-code)
else()
    set(DOTENV_COMPILE_OPTIONS -O3)
endif()

# Target names
set(DOTENV_C_SHARED ${PROJECT_NAME})
set(DOTENV_C_STATIC "${PROJECT_NAME}-s")
set(DOTENV_C_TEST "${PROJECT_NAME}-test")

# File locations
set(DOTENV_C_INCLUDE src)
set(DOTENV_C_INSTALL_INCLUDE ${DOTENV_C_INCLUDE}/dotenv.h)
file(GLOB DOTENV_C_SRC CONFIGURE_DEPENDS
        src/*.c
        )
file(GLOB DOTENV_C_TEST_SRC CONFIGURE_DEPENDS
        src/*.c
        test/*.c
        )

# Add targets
if (DOTENV_SHARED)
    add_library(${DOTENV_C_SHARED} SHARED ${DOTENV_C_SRC})
    target_include_directories(${DOTENV_C_SHARED} PRIVATE ${DOTENV_C_INCLUDE})
    target_compile_options(${DOTENV_C_SHARED} PRIVATE ${DOTENV_COMPILE_OPTIONS})
    set_target_properties(${DOTENV_C_SHARED} PROPERTIES PUBLIC_HEADER ${DOTENV_C_INSTALL_INCLUDE})
    install(TARGETS ${DOTENV_C_SHARED}
            LIBRARY DESTINATION bin
            PUBLIC_HEADER DESTINATION include)
endif()

if (DOTENV_STATIC)
    add_library(${DOTENV_C_STATIC} STATIC ${DOTENV_C_SRC})
    target_include_directories(${DOTENV_C_STATIC} PRIVATE ${DOTENV_C_INCLUDE})
    target_compile_options(${DOTENV_C_STATIC} PRIVATE ${DOTENV_COMPILE_OPTIONS})
    set_target_properties(${DOTENV_C_STATIC} PROPERTIES PUBLIC_HEADER ${DOTENV_C_INSTALL_INCLUDE})
    install(TARGETS ${DOTENV_C_STATIC}
            LIBRARY DESTINATION bin
            PUBLIC_HEADER DESTINATION include)
endif()

if (DOTENV_TEST)
    enable_testing()
    add_executable(${DOTENV_C_TEST} ${DOTENV_C_TEST_SRC})
    target_include_directories(${DOTENV_C_TEST} PRIVATE ${DOTENV_C_INCLUDE})
    target_compile_options(${DOTENV_C_TEST} PRIVATE ${DOTENV_COMPILE_OPTIONS})

    configure_file(test/.env ${CMAKE_BINARY_DIR}/test/.env COPYONLY)
    configure_file(test/.test.env ${CMAKE_BINARY_DIR}/test/.test.env COPYONLY)

    add_test(NAME ${DOTENV_C_TEST} COMMAND ${DOTENV_C_TEST})
endif()

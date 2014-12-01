cmake_minimum_required(VERSION 2.8.12)
project(cpp-json-benchmark C CXX)

# Project Output Paths

SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")

# Set compiler-specific flags

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-reorder -Wno-unused-parameter -Wno-deprecated-register")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Wno-unused-parameter -pthread")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
endif()

set(MAINFOLDER ${PROJECT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")

set(VENDOR_DIRECTORY "${PROJECT_SOURCE_DIR}/vendor")
list(APPEND CMAKE_MODULE_PATH ${VENDOR_DIRECTORY})


# Set include directories

include_directories(
    SYSTEM "${VENDOR_DIRECTORY}/hayai/src"
    SYSTEM "${VENDOR_DIRECTORY}/rapidjson/include"
    SYSTEM "${VENDOR_DIRECTORY}/picojson"
    SYSTEM "${VENDOR_DIRECTORY}/jsoncpp"
)

# Add the main binary

add_subdirectory(src)

# Add cpplint target

include(FindPythonInterp)
if (NOT PYTHONINTERP_FOUND)
    message(STATUS "Python not found; 'cpplint' target will not be available")
else()
    set(CPPLINT_FILTER
        "-build/include"
        "-legal/copyright"
        "-runtime/references"
        "-build/header_guard"
        "-readability/streams"
        "-whitespace/line_length"
        "-build/c++11"
        "-whitespace/indent"
    )

    FILE (GLOB_RECURSE ALL_SOURCES src/*.cpp src/*.h test/*.cpp test/*.h)

    set(CPPLINT_PATH "${MAINFOLDER}/ext/cpplint.py")

    set(CPPLINT_ARGS "")
    if (CPPLINT_FILTER)
        string(REPLACE ";" "," CPPLINT_FILTER "${CPPLINT_FILTER}")
        set(CPPLINT_ARGS "${CPPLINT_ARGS}--filter=${CPPLINT_FILTER}")
    endif()
    if (MSVC)
        set(CPPLINT_ARGS "${CPPLINT_ARGS} --output=vs7")
    endif()

    ADD_CUSTOM_TARGET(cpplint
        COMMAND ${PYTHON_EXECUTABLE} ${CPPLINT_PATH} ${CPPLINT_ARGS} ${ALL_SOURCES}
        VERBATIM
    )
endif()

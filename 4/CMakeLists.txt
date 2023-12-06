# Copyright 2022 Klaas Kliffen
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required (VERSION 3.16)

project(4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(SOURCES1
    ${SOURCE_DIR}/main.cpp
)

# set(SOURCES2
#     ${SOURCE_DIR}/second.cpp
#     ${SOURCE_DIR}/common.cpp
# )

add_executable(aoc_${PROJECT_NAME}.1 ${SOURCES1})
target_link_libraries(aoc_${PROJECT_NAME}.1 Util)

# add_executable(aoc_${PROJECT_NAME}.2 ${SOURCES2})
# target_link_libraries(aoc_${PROJECT_NAME}.2 Util)

# Copyright 2023 Klaas Kliffen
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required (VERSION 3.16)

project(Util)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

set(SOURCES
    ${SOURCE_DIR}/util.cpp
)

add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" ${PROJECT_SOURCE_DIR}/include)

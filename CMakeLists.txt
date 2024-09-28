cmake_minimum_required(VERSION 3.5.0)
project(BatToExe VERSION 0.1.0 LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(BatToExe ${SOURCES})
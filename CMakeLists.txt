cmake_minimum_required(VERSION 3.5.0)
project(BatToExe VERSION 0.1.0 LANGUAGES C)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SOURCES
        ${PROJECT_SOURCE_DIR}/include/*.h
        ${PROJECT_SOURCE_DIR}/src/*.c)

add_executable(${PROJECT_NAME} ${SOURCES})

# Ejecuta el programa despues de hacer la build
add_custom_command(TARGET ${PROJECT_NAME} 
        POST_BUILD
        COMMAND ${CMAKE_BINARY_DIR}/${PROJECT_NAME} 
                ${PROJECT_SOURCE_DIR}/test_files/script.bat
                ${PROJECT_SOURCE_DIR}/test_files/script.exe
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
cmake_minimum_required(VERSION 3.16)
project(kolokwiumDlaStudentow)

set(CMAKE_CXX_STANDARD 14)
add_executable(${PROJECT_NAME} main.cpp PtrCStringVector.cpp)
add_subdirectory(tests)

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(valgrind_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
    COMMAND
        valgrind --leak-check=full ${CMAKE_CURRENT_BINARY_DIR}/valgrind_${PROJECT_NAME})

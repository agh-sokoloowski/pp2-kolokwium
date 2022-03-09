# 'Google_test' is the subproject name
project(tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(${PROJECT_NAME} PtrCStringVectorTests.cpp ../PtrCStringVector.cpp)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)

add_custom_target(run_${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_target(valgrind_${PROJECT_NAME} DEPENDS ${PROJECT_NAME}
    COMMAND
        valgrind --leak-check=full ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME})

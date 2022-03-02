cmake_minimum_required(VERSION 3.0.0)
project(Buzz-22 VERSION 0.1.0)

add_subdirectory (core/src)
add_subdirectory (core/test)

include(CTest)
enable_testing()
add_test (NAME BuzzTest COMMAND Test)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

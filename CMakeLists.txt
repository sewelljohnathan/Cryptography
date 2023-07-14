
cmake_minimum_required(VERSION 3.22)
project (cryptography LANGUAGES CXX)

include (${CMAKE_CURRENT_LIST_DIR}/includes/CMakeLists.txt)
include (${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC -Wall -Wextra)

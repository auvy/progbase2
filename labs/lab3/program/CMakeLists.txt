cmake_minimum_required(VERSION 2.8.9)

project(a.out)

include_directories(${CMAKE_SOURCE_DIR}/../libcsvlab)
link_directories(${CMAKE_SOURCE_DIR}/../libcsvlab/build)
file(GLOB SOURCES "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} csvlab)

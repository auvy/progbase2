cmake_minimum_required(VERSION 2.8.9)

project(csvlab)


file(GLOB SOURCES "*.c")

#Generate the shared (STATIC, SHARED or MODULE) library from the sources
add_library(${PROJECT_NAME} STATIC ${SOURCES})

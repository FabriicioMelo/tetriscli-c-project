cmake_minimum_required(VERSION 3.25.3)
project(TetrisCLI)

#DIRECTORIES
set(SRC_DIR "${PROJECT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

file(GLOB SRC_FILES CONFIGURE_DEPENDS
  src/*.c
)

add_executable(${PROJECT_NAME} ${SRC_FILES})
include_directories(${INCLUDE_DIR})
cmake_minimum_required(VERSION 3.13) 
project(waphics)              

set(SOURCE_FILES src/builder.c)

add_executable(waphics ${SOURCE_FILES})

enable_testing()

add_subdirectory(tests)

install(TARGETS waphics DESTINATION bin)
cmake_minimum_required(VERSION 3.13) 
project(waphics)              

set(SOURCE_FILES src/builder.c)

add_executable(waphics ${SOURCE_FILES})

install(TARGETS waphics DESTINATION bin)
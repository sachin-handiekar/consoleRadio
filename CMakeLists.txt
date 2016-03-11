cmake_minimum_required(VERSION 3.3)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

project(consoleRadio)

include_directories(include)

file( GLOB_RECURSE PROJ_SOURCES src/*.c )
file( GLOB_RECURSE PROJ_HEADERS include/*.h )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -c")

set(SOURCE_FILES src/main.c)

add_executable(consoleRadio ${PROJ_SOURCES})

# set the path to the library folder
link_directories(/usr/local/lib)

find_library(CURL_LIB curl)
find_library(MPG123_LIB mpg123)
find_library(AO_LIB ao)

# link the libraries to the executable
target_link_libraries (consoleRadio ${CURL_LIB} ${MPG123_LIB} ${AO_LIB})

cmake_minimum_required (VERSION 3.11)
project (PodcastPackager)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB SourcesCpp src/*.cpp)
add_executable(FeedParser ${SourcesCpp})

FILE(GLOB TestsCpp test/*.cpp)
set(TestsSourcesCpp ${SourcesCpp})
list(REMOVE_ITEM TestsSourcesCpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
message("${TestsSourcesCpp}")
add_executable(Test ${TestsCpp} ${TestsSourcesCpp})

target_link_libraries(FeedParser ${CONAN_LIBS})
target_link_libraries(Test ${CONAN_LIBS})
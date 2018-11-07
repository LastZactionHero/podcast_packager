cmake_minimum_required (VERSION 3.11)
project (PodcastPackager)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_executable(FeedParser src/main.cpp)
add_executable(Test test/main.cpp)

target_link_libraries(FeedParser ${CONAN_LIBS})
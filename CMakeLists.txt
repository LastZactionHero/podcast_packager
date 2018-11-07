cmake_minimum_required (VERSION 3.11)
project (PodcastPackager)

include(conanbuildinfo.cmake)
conan_basic_setup()

add_executable(FeedParser src/main.cpp src/global_config_service.cpp)
add_executable(Test test/main.cpp src/global_config_service.cpp test/global_config_service_test.cpp)

target_link_libraries(FeedParser ${CONAN_LIBS})
target_link_libraries(Test ${CONAN_LIBS})
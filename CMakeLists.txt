cmake_minimum_required (VERSION 3.11)
project (PodcastPackager)

include(conanbuildinfo.cmake)
conan_basic_setup()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB SourcesCpp src/*.cpp)
list(REMOVE_ITEM SourcesCpp ${CMAKE_CURRENT_SOURCE_DIR}/src/transfer.cpp)
list(REMOVE_ITEM SourcesCpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

set(PodcastPackagerCpp ${SourcesCpp})
list(APPEND PodcastPackagerCpp ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
add_executable(PodcastPackager ${SourcesCpp})

set(TransferSourcesCpp ${SourcesCpp})
list(APPEND TransferSourcesCpp ${CMAKE_CURRENT_SOURCE_DIR}/src/transfer.cpp)
add_executable(Transfer ${TransferSourcesCpp})

FILE(GLOB TestsCpp test/*.cpp)
set(TestsSourcesCpp ${SourcesCpp})
add_executable(Test ${TestsCpp} ${TestsSourcesCpp})

target_link_libraries(PodcastPackager ${CONAN_LIBS})
target_link_libraries(Transfer ${CONAN_LIBS})
target_link_libraries(Test ${CONAN_LIBS})
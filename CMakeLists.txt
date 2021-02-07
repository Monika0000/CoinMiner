cmake_minimum_required(VERSION 3.16)
project(CoinMiner C)

set(CMAKE_C_STANDARD 90)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

configure_file(depends/bin/libcurl.dll libcurl.dll COPYONLY)
configure_file(depends/bin/libcurl.lib libcurl.lib COPYONLY)
configure_file(depends/bin/libcurl_imp.lib libcurl_imp.lib COPYONLY)

add_executable(CoinMiner main.c unit_test.h https_util.h)
target_link_libraries(CoinMiner libcurl libcurl_imp)
#add_library(libcurl libcurl.dll)
#set_target_properties(libcurl PROPERTIES LINKER_LANGUAGE C)

target_include_directories(CoinMiner
    PUBLIC depends
)
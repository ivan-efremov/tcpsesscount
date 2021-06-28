cmake_minimum_required(VERSION 3.2.2)

project(tests)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "-pipe -DDEBUG -Wall -gdwarf-3 -gstrict-dwarf -O0 ${CMAKE_C_FLAGS_ALL}")

set(CMAKE_C_FLAGS_RELEASE "-pipe -DNDEBUG -Wall -g0 -O2 -s ${CMAKE_C_FLAGS_ALL}")


include_directories("${CMAKE_SOURCE_DIR}")


find_library(LIB_CUNIT libcunit.so)

add_executable(tests ../array_unique.c test1.c main.c)

target_link_libraries(tests ${LIB_CUNIT})

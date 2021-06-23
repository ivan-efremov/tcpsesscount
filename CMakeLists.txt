cmake_minimum_required(VERSION 3.2.2)

project(tcpsesscount)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS_DEBUG "-pipe -DDEBUG -Wall -gdwarf-3 -gstrict-dwarf -O0 ${CMAKE_C_FLAGS_ALL}")

set(CMAKE_C_FLAGS_RELEASE "-pipe -DNDEBUG -Wall -g0 -O2 -s ${CMAKE_C_FLAGS_ALL}")


set(SOURCE_FILES main.c)


find_library(LIB_PCAP libpcap.so)

add_executable(tcpsesscount ${SOURCE_FILES})

target_link_libraries(tcpsesscount ${LIB_PCAP})

cmake_minimum_required(VERSION 3.15)
project(Socket_programming C)

set(CMAKE_C_STANDARD 99)

add_executable(Socket_programming port_scanner.c)
#add_executable(Socket_programming client.c)
#add_executable(Socket_programming server.c)
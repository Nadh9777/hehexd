cmake_minimum_required(VERSION 3.24)
project(ProjectUnix_2ING1_BouthaynaNalouti C)

set(CMAKE_C_STANDARD 11)

include_directories(Tubes)
include_directories(Sockets)

add_executable(ProjectUnix_2ING1_BouthaynaNalouti
        Tubes/Client.c
        Tubes/Handlers_Cli.h
        Tubes/Handlers_Serv.h
        Tubes/serv_cli_fifo.h
        Tubes/Server.c
        Sockets/Client.c
        Sockets/Server.c
        Sockets/Server_Client.h)

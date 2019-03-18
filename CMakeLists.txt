cmake_minimum_required(VERSION 3.13)
project(ac_automation)

set(CMAKE_CXX_STANDARD 11)

add_executable(ac_automation main.cpp Automation.cpp Node.h)
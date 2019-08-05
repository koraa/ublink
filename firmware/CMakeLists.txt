cmake_minimum_required(VERSION 3.5)

set(COMPONENTS "main;console;esptool_py;app_trace")
include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ublink)

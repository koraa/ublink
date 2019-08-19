cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS "vendor/")
set(COMPONENTS "args;main;console;esptool_py;app_trace")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(ublink)

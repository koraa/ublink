set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

idf_component_register(SRCS "ublink/ublink.cpp" INCLUDE_DIRS ".")

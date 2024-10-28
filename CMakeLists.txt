cmake_minimum_required(VERSION 3.16)

project(nco LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(nco-benchmark benchmark.cpp nco.h nco.cpp)
add_executable(nco-generate generate.cpp nco.h nco.cpp)

include(GNUInstallDirs)
install(TARGETS nco-benchmark
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS nco-generate
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

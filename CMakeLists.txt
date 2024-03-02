cmake_minimum_required(VERSION 3.5)

project(Mechanism LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Mechanism main.cpp)

include(GNUInstallDirs)
install(TARGETS Mechanism
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

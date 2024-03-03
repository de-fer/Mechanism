cmake_minimum_required(VERSION 3.5)

project(Mechanism LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(nlohmann_json REQUIRED)

add_executable(Mechanism main.cpp
    model.hpp model.cpp
    settings.hpp)

include(GNUInstallDirs)
install(TARGETS Mechanism
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    glfw
    OpenGL::GL
    nlohmann_json::nlohmann_json
)

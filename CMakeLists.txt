cmake_minimum_required(VERSION 3.22)

project(FlickeringLight VERSION 0.0.0)


set(CMAKE_CXX_STANDARD 20)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15")

set(LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(cmake/cpm.cmake)

CPMAddPackage(
    NAME SFML
    GIT_TAG 2.6.2
    VERSION 2.6.2
    GITHUB_REPOSITORY SFML/SFML
    SOURCE_DIR ${LIB_DIR}/SFML
)

enable_testing()

add_subdirectory(app)

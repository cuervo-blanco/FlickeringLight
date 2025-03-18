cmake_minimum_required(VERSION 3.22)

add_executable(FlickeringLight)

set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/flickering_light")

target_sources(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/command_handler.cpp
    ${INCLUDE_DIR}/command_handler.h)
        

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(FlickeringLight PRIVATE sfml-system sfml-window sfml-graphics)

include_directories(${CMAKE_SOURCE_DIR}/libs/SFML/include)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/..)


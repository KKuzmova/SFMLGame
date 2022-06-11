cmake_minimum_required(VERSION 3.21)
project(BlueBox)

set(CMAKE_CXX_STANDARD 17)

add_executable(BlueBox main.cpp Game.cpp Game.h Player.cpp Player.h Cubes.cpp Cubes.h)

include_directories(sounds images fonts)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/sounds DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(/usr/local/include)
find_package(SFML COMPONENTS system window graphics network audio REQUIRED)
target_link_libraries(BlueBox sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

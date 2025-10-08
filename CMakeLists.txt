cmake_minimum_required(VERSION 3.28)
project(SFMLGame LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.2
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

file(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

add_executable(game "src/Main.cpp" "src/Window.h" "src/Window.cpp" "src/Application.cpp" "src/Utils.h" "src/Layer.h" "src/Layer.cpp" "src/GameLayer.h" "src/GameLayer.cpp" "src/OverlayLayer.h" "src/OverlayLayer.cpp" "src/MenuLayer.h" "src/MenuLayer.cpp" "src/Eagle.h" "src/Eagle.cpp" "src/Entity.h"  "src/Ball.h" "src/Ball.cpp" "src/Player.h" "src/Player.cpp" "src/Entity.cpp" "src/Wall.h" "src/Wall.cpp")
target_compile_features(game PRIVATE cxx_std_20)
target_link_libraries(game PRIVATE SFML::Graphics SFML::Audio)

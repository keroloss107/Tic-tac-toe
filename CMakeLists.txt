cmake_minimum_required(VERSION 3.10)
project(TicTacToeProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC fix: prevent static/dynamic CRT mismatch in debug builds
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "_d")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# === Include Directories ===
include_directories(include)

# === Qt GUI ===
find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# === Game Source Files ===
set(GAME_SOURCES
    Game_Logic/Board.cpp
    Game_Logic/AI.cpp
    Game_Logic/Game.cpp
)

set(GAME_HEADERS
    include/Board.h
    include/AI.h
    include/Game.h
)

# === Build shared game logic as a library ===
add_library(tictactoe_lib ${GAME_SOURCES} ${GAME_HEADERS})

# === Main Game Executable ===
add_executable(tictactoe Game_Logic/main.cpp GUI/mainwindow.cpp GUI/mainwindow.ui)
target_link_libraries(tictactoe PRIVATE tictactoe_lib Qt6::Widgets)

# === GoogleTest (submodule) ===
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# === Test Sources ===
set(TEST_SOURCES
    tests/test_board.cpp
    tests/test_ai.cpp
    tests/test_game.cpp
    tests/test_integration.cpp
)

add_executable(board_tests ${TEST_SOURCES})
target_link_libraries(board_tests
    tictactoe_lib
    gtest
    gtest_main
)

include(GoogleTest)
enable_testing()
gtest_discover_tests(board_tests)

cmake_minimum_required(VERSION 3.10)
project(TicTacToeProject)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC fix: shared CRT
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "_d")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# ==== Source Files ====
set(GAME_SOURCES
    SRC/Board.cpp
    SRC/AI.cpp
    SRC/Game.cpp
)

set(GAME_HEADERS
    SRC/Board.h
    SRC/AI.h
    SRC/Game.h
)

# ==== Create a library for reuse ====
add_library(tictactoe_lib ${GAME_SOURCES} ${GAME_HEADERS})

# ==== Main Game Executable ====
add_executable(tictactoe SRC/main.cpp)
target_link_libraries(tictactoe tictactoe_lib)

# ==== Google Test ====
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# ==== Tests ====
set(TEST_SOURCES
    tests/test_board.cpp
    tests/test_ai.cpp
    tests/test_game.cpp
)

add_executable(board_tests ${TEST_SOURCES})
target_link_libraries(board_tests
    tictactoe_lib
    gtest
    gtest_main
)

# ==== Google Test Integration ====
include(GoogleTest)
enable_testing()
gtest_discover_tests(board_tests)

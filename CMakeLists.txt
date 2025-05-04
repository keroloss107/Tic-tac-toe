cmake_minimum_required(VERSION 3.10)
project(TicTacToeProject)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fix for MSVC: prevent linker errors due to static/dynamic CRT mismatch
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "_d")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# ==== Game Source Files ====
set(GAME_SOURCES
    SRC/Board.cpp
    SRC/AI.cpp
    SRC/Game.cpp
    SRC/main.cpp
)

# Create the main game executable
add_executable(tictactoe ${GAME_SOURCES})

# ==== Google Test ====
# Cloned from GitHub into "googletest/" folder
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# ==== Test Source Files ====
set(TEST_SOURCES
    tests/test_board.cpp
    tests/test_ai.cpp
    tests/test_game.cpp
    SRC/Board.cpp       
    SRC/AI.cpp
    SRC/Game.cpp
)

# Create test executable
add_executable(board_tests ${TEST_SOURCES})

# Link against Google Test
target_link_libraries(board_tests gtest gtest_main)

# ==== Google Test Integration ====
include(GoogleTest)
gtest_discover_tests(board_tests)

# Enable CMake test runner
enable_testing()

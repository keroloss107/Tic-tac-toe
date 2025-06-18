cmake_minimum_required(VERSION 3.16)
project(TicTacToeProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC-specific settings
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "_d")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# Include paths
include_directories(include GUI)

# Detect Qt only on Windows (for GUI)
if(WIN32)
    set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64")
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
endif()

# === Game Logic ===
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

add_library(tictactoe_lib ${GAME_SOURCES} ${GAME_HEADERS})

# === GUI === (only build on Windows)
if(WIN32)
    set(GUI_SOURCES
        GUI/main_gui.cpp
        GUI/TicTacToe.cpp
        GUI/MainMenuWindow.cpp
        GUI/LoginWindow.cpp
        GUI/RegisterWindow.cpp
        GUI/GameModeWindow.cpp
        GUI/GameHistoryWindow.cpp
        GUI/DatabaseManager.cpp
    )

    add_executable(tictactoe ${GUI_SOURCES})
    target_link_libraries(tictactoe tictactoe_lib Qt6::Core Qt6::Gui Qt6::Widgets)
endif()

# === Testing ===
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

set(TEST_SOURCES
    tests/test_board.cpp
    tests/test_ai.cpp
    tests/test_game.cpp
    tests/test_integration.cpp
)

add_executable(board_tests ${TEST_SOURCES})
target_link_libraries(board_tests tictactoe_lib gtest gtest_main)

include(GoogleTest)
enable_testing()
gtest_discover_tests(board_tests)

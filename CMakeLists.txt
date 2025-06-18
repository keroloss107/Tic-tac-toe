cmake_minimum_required(VERSION 3.16)
project(TicTacToeProject)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC Debug postfix (useful for windeployqt)
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "_d")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# === Include Paths ===
include_directories(include GUI)

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

# === GUI Files (Only on Windows) ===
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

    # Find Qt 6 (Core, GUI, Widgets)
    find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

    # Main GUI executable
    add_executable(tictactoe ${GUI_SOURCES})
    target_link_libraries(tictactoe
        tictactoe_lib
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
    )
endif()

# === Google Test (submodule) ===
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

# === Unit & Integration Tests ===
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

# === Enable Test Discovery ===
include(GoogleTest)
enable_testing()
gtest_discover_tests(board_tests)

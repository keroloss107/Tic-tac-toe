cmake_minimum_required(VERSION 3.10)
project(TicTacToeProject)

# Use C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# MSVC fix: prevent static/dynamic CRT mismatch in debug builds
if(MSVC)
    set(CMAKE_DEBUG_POSTFIX "_d")
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

# === Qt Setup ===
set(CMAKE_PREFIX_PATH "C:/Qt/6.9.1/msvc2022_64/lib/cmake")  # Adjust if different
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# === UI Compilation ===
qt6_wrap_ui(UI_HEADERS
    GUI/LoginWindow.ui
    GUI/MainMenuWindow.ui
    GUI/GameModeWindow.ui
    GUI/RegisterWindow.ui
    GUI/GameHistoryWindow.ui
    GUI/TicTacToe.ui
)

# === Include Directories ===
include_directories(include)

# === Game Logic Files ===
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

# === GUI Sources ===
set(GUI_SOURCES
    GUI/main_gui.cpp
    GUI/DatabaseManager.cpp
    GUI/Game_gui.cpp
    GUI/GameHistoryWindow.cpp
    GUI/GameModeWindow.cpp
    GUI/LoginWindow.cpp
    GUI/MainMenuWindow.cpp
    GUI/RegisterWindow.cpp
    GUI/TicTacToe.cpp
)

# === GUI Headers ===
set(GUI_HEADERS
    include/DatabaseManager.h
    include/Game_gui.h
    include/GameHistoryWindow.h
    include/GameModeWindow.h
    include/LoginWindow.h
    include/MainMenuWindow.h
    include/RegisterWindow.h
    include/TicTacToe.h
)

# === Create Game Library ===
add_library(tictactoe_lib ${GAME_SOURCES} ${GAME_HEADERS})

# === Main Executable ===
add_executable(Tictactoe_Project ${GUI_SOURCES} ${GUI_HEADERS} ${UI_HEADERS})
target_link_libraries(Tictactoe_Project
    tictactoe_lib
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# === GoogleTest ===
add_subdirectory(googletest)
include_directories(googletest/googletest/include)

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

# === Google Test Integration ===
include(GoogleTest)
enable_testing()
gtest_discover_tests(board_tests)

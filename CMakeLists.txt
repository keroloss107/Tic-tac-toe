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

# === Include Directories ===
include_directories(include)
include_directories(GUI)

# === Find Qt ===
set(Qt6_DIR "C:/Qt/6.9.1/msvc2022_64/lib/cmake/Qt6")
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# === Game Logic Source Files ===
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
    GUI/TicTacToe.cpp
    GUI/MainMenuWindow.cpp
    GUI/LoginWindow.cpp
    GUI/RegisterWindow.cpp
    GUI/GameModeWindow.cpp
    GUI/GameHistoryWindow.cpp
    GUI/DatabaseManager.cpp
)

# === UI Headers === (optional if using `uic` manually elsewhere)

# === Build shared game logic as a library ===
add_library(tictactoe_lib ${GAME_SOURCES} ${GAME_HEADERS})

# === Main Game Executable ===
add_executable(tictactoe ${GUI_SOURCES})
target_link_libraries(tictactoe
    tictactoe_lib
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

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

# === Google Test Integration ===
include(GoogleTest)
enable_testing()
gtest_discover_tests(board_tests)

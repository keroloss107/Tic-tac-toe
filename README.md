# 🎮 Advanced Tic Tac Toe Game

An enhanced version of the classic Tic Tac Toe game with intelligent AI, secure user accounts, and replayable game history — built using modern C++ and Qt.

---

## 📘 Overview

This project reimagines the traditional Tic Tac Toe game with advanced features like:
- **User authentication**
- **Strategic AI opponent**
- **Game history tracking**
- **Modern GUI**
- **Robust testing and CI/CD workflows**

Designed for an academic embedded systems project, it applies best practices in software design, testing, and version control.

---

## 🚀 Features

- ✅ Player vs Player and Player vs AI modes
- 🧠 AI powered by Minimax with alpha-beta pruning
- 🔐 Secure login and registration system with password hashing
- 🗂️ Personalized game history per user with replay capability
- 🖼️ Graphical interface using Qt framework
- 🧪 Unit and integration tests with Google Test
- 🔄 GitHub Actions CI/CD integration
- 📊 Performance optimization with metrics logging

---

## 🛠️ Tech Stack

| Area             | Tools Used                        |
|------------------|-----------------------------------|
| Language         | C++ (Object-Oriented)             |
| GUI Framework    | Qt                                |
| Testing          | Google Test                       |
| Version Control  | Git + GitHub                      |
| CI/CD            | GitHub Actions                    |
| Data Storage     | SQLite                            |
| Security         | Password hashing (e.g., SHA-256)  |

---

## 📁 Project Structure

TicTacToeProject/
│
├── .github/ # CI/CD workflow configurations (GitHub Actions)
├── GUI/ # All UI components and interface logic
├── Game_Logic/ # Core game mechanics and AI logic
├── googletest/ # Google Test framework (via submodule)
├── tests/ # Unit & integration test cases
├── .gitignore # Git ignored files list
├── .gitmodules # Git submodules configuration
└── CMakeLists.txt # Project build configuration

---

## 🧪 Testing & Quality Assurance

- **Framework**: Google Test
- **Types**:
  - Unit tests for game logic, AI, and database interactions
  - Integration tests for full flow validation
- **CI Integration**: Automated via GitHub Actions on every push/pull request

---

## 📦 Continuous Deployment (CD)

- GitHub Actions handles not just testing, but also deployment.
- On every successful push to the main branch:
  - The project is built in a clean environment.
  - Artifacts (like executables) can be uploaded to GitHub Releases.
- This ensures a fully automated pipeline from development to delivery.

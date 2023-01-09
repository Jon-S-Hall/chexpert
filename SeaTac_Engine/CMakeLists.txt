cmake_minimum_required(VERSION 3.23)
project(SeaTac_Engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(SeaTac_Engine ChessGame.cpp ChessGame.h GameState.cpp GameState.h ChessPlayer.cpp ChessPlayer.h SeaEngine.cpp SeaEngine.h SeaChessUtils.h SeaChessUtils.cpp HumanPlayer.cpp HumanPlayer.h main.cpp)

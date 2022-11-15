cmake_minimum_required(VERSION 3.23)
project(SeaTac_Engine)

set(CMAKE_CXX_STANDARD 17)

add_executable(SeaTac_Engine main.cpp ChessGame.cpp ChessGame.h SeaTac_Engine.cpp SeaTac_Engine.h bitboard.cpp bitboard.h GameState.cpp GameState.h SeaEngine.cpp SeaEngine.h)

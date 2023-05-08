#pragma once

#ifdef MINIMAX_EXPORTS
#define MINIMAX_API __declspec(dllexport)
#else
#define MINIMAX_API __declspec(dllimport)
#endif

extern "C" MINIMAX_API int getWinner(int field[3][3]);
extern "C" MINIMAX_API void getNextMove(int field[3][3], int& x, int& y);
extern "C" MINIMAX_API bool isDraw(int field[3][3]);
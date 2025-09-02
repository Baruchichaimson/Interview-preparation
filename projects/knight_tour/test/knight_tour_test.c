#include <stdio.h>

#include "knight_tour.h"

int main()
{
    size_t board[CHESS_LEN][CHESS_LEN] = { 0 };
    chess_square_t start_square = {0,0};

    KnightTour(board, start_square, 0);
    PrintBoard(board);
    KnightTour(board, start_square, 1);
    PrintBoard(board);

    return 0;
}
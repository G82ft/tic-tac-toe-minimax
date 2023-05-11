#include "pch.h"
#include "minimax.h"
#include <algorithm>
#include <iostream>


int getWinner(int field[3][3]) {
    if (((
            // Checking left to right diagonal
            field[0][0] == field[1][1]
            && field[2][2] == field[1][1]
        ) || (
            // Checking right to left diagonal
            field[2][0] == field[1][1]
            && field[0][2] == field[1][1]
    ))) {
        return field[1][1];
    }

    for (int i = 0; i < 3; i++) {
        if (
                field[0][i] == field[1][i]
                && field[1][i] == field[2][i]
        ) {
            return field[2][i];
        }
    }

    for (int i = 0; i < 3; i++) {
        if (
            std::count(field[i], field[i] + 3, field[i][0])
            == 3
        ) {
            return field[i][0];
        }
    }

    return 0;
}

bool isDraw(int field[3][3]) {
    int count = 9;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] == 0) {
                count--;
            }
        }
    }

    return count == 9;
}

void copy2d(int** from, int** to, int xSize, int ySize) {
    for (int i = 0; i < xSize; i++) {
        to[i] = new int[ySize];
        for (int j = 0; j < ySize; j++) {
            to[i][j] = from[i][j];
        }
    }
}

int*** getActions(int** field, int& size, int turn = -1) {
    int*** actions = new int**[9];
    size = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (field[i][j] != 0) {
                continue;
            }
            actions[size] = new int* [3];
            copy2d(field, actions[size], 3, 3);
            actions[size][i][j] = turn;
            size++;
        }
    }

    return actions;
}

void deallocate(int*** array3d, int xSize, int ySize, int zSize) {
    for (int x = 0; x < xSize; x++) {
        for (int y = 0; y < ySize; y++) {
            delete[] array3d[x][y];
        }
        delete[] array3d[x];
    }
    delete[] array3d;
}

void deallocate(int** array2d, int xSize, int ySize) {
    for (int x = 0; x < xSize; x++) {
        delete[] array2d[x];
    }
    delete[] array2d;
}

int evaluate(int** field, int turn = -1) {
    int fieldArray[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            fieldArray[i][j] = field[i][j];
        }
    }

    if (getWinner(fieldArray) != 0) {
        return getWinner(fieldArray);
    } else if(isDraw(fieldArray)) {
        return 0;
    }

    if (turn == 1) {
        int value = INT_MIN, size = 0;

        int*** actions = getActions(field, size, turn);

        for (int i = 0; i < size; i++) {
            value = max(value, evaluate(actions[i], turn * -1));
        }

        deallocate(actions, size, 3, 3);

        return value;
    }
    else {
        int value = INT_MAX, size = 0;

        int*** actions = getActions(field, size);

        for (int i = 0; i < size; i++) {
            value = min(value, evaluate(actions[i], turn * -1));
        }

        deallocate(actions, size, 3, 3);

        return value;
    }
}

void getNextMove(int field[3][3], int& x, int& y) {
    int size = 0;
    int** fieldCopy = new int*[3];

    for (int i = 0; i < 3; i++) {
        fieldCopy[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            fieldCopy[i][j] = field[i][j];
        }
    }

    int*** actions = getActions(fieldCopy, size);

    int min = INT_MAX, index = 0;

    for (int i = 0; i < size; i++) {
        int result = evaluate(actions[i], 1);
        if (result < min) {
            min = result;
            index = i;
        }
    }

    for (int j = 0; j < 3; j++) {
        for (int k = 0; k < 3; k++) {
            if (actions[index][j][k] == fieldCopy[j][k]) {
                continue;
            }
            x = j;
            y = k;

            deallocate(actions, size, 3, 3);
            deallocate(fieldCopy, 3, 3);

            return;
        }
    }
}

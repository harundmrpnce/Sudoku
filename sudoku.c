#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 9

int isSafe(int grid[N][N], int row, int col, int num) {

    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num) {
            return 0;
        }
    }
    
    for (int i = 0; i < N; i++) {
        if (grid[i][col] == num) {
            return 0;
        }
    }
    
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0;
            }
        }
    }
    
    return 1;
}

int solveSudoku(int grid[N][N]) {
    int row, col;
    int isEmpty = 0;
    
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0) {
                isEmpty = 1;
                break;
            }
        }
        if (isEmpty) {
            break;
        }
    }

    if (!isEmpty) {
        return 1;
    }
    
    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            
            if (solveSudoku(grid)) {
                return 1;
            }
            
            grid[row][col] = 0;
        }
    }
    
    return 0;
}

void generateRandomSudoku(int grid[N][N]) {
    
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            grid[row][col] = 0;
        }
    }

    srand(time(NULL));

    for (int diag = 0; diag < N; diag += 3) {
        for (int i = 0; i < 3; i++) {
            int num = (rand() % 9) + 1; 

            bool isPresent = false;
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (grid[diag + j][diag + k] == num) {
                        isPresent = true;
                        break;
                    }
                }
                if (isPresent) {
                    break;
                }
            }

            if (!isPresent) {
                grid[diag + i][diag + i] = num;
            }
        }
    }

    solveSudoku(grid);
}

void copyGrid(int source[N][N], int destination[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            destination[row][col] = source[row][col];
        }
    }
}

void createUnsolvedSudoku(int solvedGrid[N][N], int unsolvedGrid[N][N], int numCellsToRemove) {
    copyGrid(solvedGrid, unsolvedGrid);

    srand(time(NULL));

    for (int i = 0; i < numCellsToRemove; i++) {
        int row = rand() % N;
        int col = rand() % N;

        if (unsolvedGrid[row][col] == 0) {
            i--;
            continue;
        }

        unsolvedGrid[row][col] = 0;
    }
}

void promptToViewSolution() {
    printf("\nPress Enter to view the solution...");
    while (getchar() != '\n') {
    }
}

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d ", grid[row][col]);
        }
        printf("\n");
    }
}

int main() {
    int solvedGrid[N][N];
    int unsolvedGrid[N][N];

    generateRandomSudoku(solvedGrid);

    int numCellsToRemove = 40;
    createUnsolvedSudoku(solvedGrid, unsolvedGrid, numCellsToRemove);

    printf("Unsolved Sudoku game:\n");
    printGrid(unsolvedGrid);

    promptToViewSolution();

    printf("\nSolved Sudoku game:\n");
    printGrid(solvedGrid);

    return 0;
}

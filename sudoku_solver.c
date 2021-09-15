#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_ROWS 9
#define NUM_COLS 9

typedef int **Game; 

Game createGame();
void printGame(Game g);
void printBorderRow(void);
void setNum(Game g, int row, int col, int num);
bool validCoOrd(int row, int col);
bool validNum(int num);
bool possible(Game g, int row, int col, int num);
void inputMap(Game g);
bool solve(Game g);
bool completed(Game g);
void confirmValid(Game g);
void freeGame(Game g);

int main(void) {
    Game g = createGame();

    inputMap(g);
    
    printf("Starter Map: \n");
    printGame(g);

    printf("Solving....\n");
    if (solve(g)) {
        printf("Sudoku solution: \n");
        printGame(g);
    } else {
        printf("No solution found\n");
    }

    // confirmValid(g);
    
    freeGame(g);
}

Game createGame() {
    Game g = malloc(NUM_ROWS * sizeof(int *));
    for (int row = 0; row < NUM_ROWS; ++row) {
        g[row] = malloc(NUM_COLS * sizeof(int));
    }

    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            g[row][col] = 0;
        }
    }
    return g;
}

void printGame(Game g) {
    printBorderRow();
    for (int row = 0; row < NUM_ROWS; ++row) {
        printf("|");
        for (int col = 0; col < NUM_COLS; ++col) {
            if (g[row][col] == 0) {
                printf(" ");
            }  else {
                printf("%d", g[row][col]);
            }
            if ((col + 1) % 3 == 0) printf("|");
        }
        printf("\n");
        if ((row + 1) % 3 == 0) {
            printBorderRow();
        }
    }
}
void printBorderRow(void) {
    for (int i = 0; i < NUM_COLS + 1 + NUM_COLS / 3; ++i) {
        printf("-");
    }
    printf("\n");
}

void setNum(Game g, int row, int col, int num) {
    if (validCoOrd(row, col) && validNum(num)) g[row][col] = num;
}

bool validCoOrd(int row, int col) {
    return ((row >= 0 && row < NUM_ROWS) && (col >= 0 && col < NUM_COLS));
}

bool validNum(int num) {
    return (num >= 0 && num <= 9);
}

bool possible(Game g, int row, int col, int num) {
    // Check Col
    for (int testRow = 0; testRow < NUM_ROWS; ++testRow) {
        if (g[testRow][col] == num) return false;
    }

    // Check Row
    for (int testCol = 0; testCol < NUM_COLS; ++testCol) {
        if (g[row][testCol] == num) return false;
    }

    // Check Square 
    int squareRowCoOrd = (row / 3) * 3;
    int squareColCoOrd = (col / 3) * 3;
    for (int testRow = squareRowCoOrd; testRow < squareRowCoOrd + NUM_ROWS / 3; ++testRow) {
        for (int testCol = squareColCoOrd; testCol < squareColCoOrd + NUM_COLS / 3; ++testCol) {
            if (g[testRow][testCol] == num) return false;
        }
    }

    return true;
}

void inputMap(Game g) {
    printf("Input game map (row col num):\n");
    int row, col, num;
    while (scanf("%d %d %d", &row, &col, &num) == 3) {
        if (!validCoOrd(row, col)) {
            printf("Invalid co-ordinates\n");
        } else if (!validNum(num)) {
            printf("Invalid number\n");
        } else if (!possible(g, row, col, num)) {
            printf("Input not possible\n");
        } else {
            setNum(g, row, col, num);
        }
    }
}

bool solve(Game g) {
    
    if (completed(g)) return true;
    
    bool contSearch = true;
    int row, col;
    for (int testRow = 0; testRow < NUM_ROWS && contSearch; ++testRow) {
        for (int testCol = 0; testCol < NUM_COLS && contSearch; ++testCol) {
            if (g[testRow][testCol] == 0) {
                contSearch = false;
                row = testRow;
                col = testCol;
            } 
        }
    }
    //printf("Trying row %d col %d\n", row, col);
    for (int num = 1; num <= NUM_ROWS; ++num) {
        if (possible(g, row, col, num)) {
            setNum(g, row, col, num);
            if (solve(g)) {
                return true;
            } else {
                setNum(g, row, col, 0);
            }
        }
    }

    return false;

}

bool completed(Game g) {
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            if (g[row][col] == 0) return false;
        }
    }

    return true;
}

void confirmValid(Game g) {
    for (int row = 0; row < NUM_ROWS; ++row) {
        for (int col = 0; col < NUM_COLS; ++col) {
            int num = g[row][col];
            setNum(g, row, col, 0);
            if (!possible(g, row, col, num)) {
                printf("Error! Found collision at row %d and col %d\n", row, col);
                return;
            }
            setNum(g, row, col, num);
        }
    }
    printf("Confirmed validity of solution!\n");
}

void freeGame(Game g) {
    for (int row = 0; row < NUM_ROWS; ++row) {
        free(g[row]);
    }
    free(g);
}
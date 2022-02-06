# Sudoku Solver

Command line based sudoku solver program. Input starting squares in sudoku and program will provide solution. Repo contains C and Python implementations of backtracking algorithm to solve sudoku. Each implementation is equivalent, however can be used for performance comparison of C vs Python.

## Files

| File | Description|
|------|-------------|
| sudoku_solver.c | C implementation of solver program |
| sudoku_solver.py | Python implementation of solver program |
| maps/ | Folder containing series of sample sudoku starting maps that can be used instead of entering in manually |

## Using solver

Both C and Python implementations being by entering each starting square in sudoku in the form `<row> <col> <number>`. Note that rows and cols are 0 indexed. Starter squares will continue to read in until EOF, after which the solver algorithm runs and outputs the solved sudoku.

### Using C Implementation

1. Compile sudoku_solver.c into executable:

        gcc sudoku_solver.c -o sudoku_solver

2. Run executable:

        ./sudoku_solver

3. Alternatively, run solver using sample input file:

        < maps/map1.txt ./sudoku_solver

### Using Python Implementation

1. Run python file through interpretter:

        python3 sudoku_solver.py

2. Alternatively, run solver using sample input file:

        < maps/map1.txt python3 sudoku_solver.py

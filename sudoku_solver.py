
NUM_ROWS = 9
NUM_COLS = 9
EMPTY_CELL = 0

ROW_BOARDER = f'+{"-" * (NUM_COLS // 3)}+{"-" * (NUM_COLS // 3)}+{"-" * (NUM_COLS // 3)}+'

class Sudoku():

    def __init__(self):
        self.board = [[EMPTY_CELL for x in range(NUM_COLS)] for y in range(NUM_ROWS)]
    
    def do_sudoku_set(self, row, col, num):
        self.board[row][col] = num
    
    def create_starter_board(self):
        while True:
            try:
                input_str = input()
                inputs = input_str.split()
                row, col, num = int(inputs[0]), int(inputs[1]), int(inputs[2])
                self.valid_move(row, col, num)
                print("Move is valid")
                self.do_sudoku_set(row, col, num)
                print("Move has been set")
            except ValueError:
                print("Failed due to value error")
                break
            except Exception:
                print("Failed due to some other error")
                break

    
    def check_if_won(self):
        for row in self.board:
            for num in row:
                if num == EMPTY_CELL:
                    return False
        return True
    
    def valid_move(self, row, col, num):
        
        if row not in range(9):
            raise ValueError("Invalid move: Row must be between 1 and 9")
        if col not in range(9):
            raise ValueError("Invalid move: Col must be between 1 and 9")
        if num not in range(1, 10):
            raise ValueError("Invalid move: Number must be between 1 and 9")

        # Checks if num already in row
        if num in self.board[row]:
            raise ValueError("Invalid move: Number already in row")

        # Checks if num is already in col
        for test_row in range(NUM_ROWS):
            if self.board[test_row][col] == num:
                raise ValueError("Invalid move: Number already in col")

        # Checks if num is already in the of 3 x 3 box which cell is in
        box_row = row // 3
        box_col = col // 3
        for test_row in range(box_row * 3, box_row * 3 + 3):
            for test_col in range(box_col * 3, box_col * 3 + 3):
                if self.board[test_row][test_col] == num:
                    raise ValueError("Invalid move: Number already in 3 x 3 Box")
    
    def solve(self):
        # If game is won, return board
        # print(self.board)
        if self.check_if_won():
            return

        # Find unfilled cell
        for test_row in range(9):
            for test_col in range(9):
                if self.board[test_row][test_col] == EMPTY_CELL:
                    row = test_row
                    col = test_col

        # Try a number to place in cell. If is valid move, try and solve board having made
        # this choice for self.board[row][col].
        for num in range(1, 10):
            try:
                self.valid_move(row, col, num)
                self.do_sudoku_set(row, col, num)
                return self.solve()
            except ValueError:
                self.do_sudoku_set(row, col, EMPTY_CELL)
        raise ValueError(f"No available moves")


    def __str__(self):
        string = ROW_BOARDER + '\n'
        for row_index, row in enumerate(self.board):
            string += '|'
            for col_index, num in enumerate(self.board[row_index]):
                if num == 0:
                    string += " "
                else:
                    string += str(num)
                if (col_index + 1) % 3 == 0:
                    string += "|"
            string += '\n'
            if (row_index + 1) % 3 == 0:
                string += ROW_BOARDER
                if row_index != NUM_ROWS - 1:
                    string += '\n'
        return string
            

s = Sudoku()
print("Enter starter grid: ")
s.create_starter_board()
print(s)

print("Solving sudoku...")
s.solve()
print(s)
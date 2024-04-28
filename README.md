A project created as practice of C++ and SFML library.

The goal is to create an app that can solve sudoku.

There are two solving algorithms:
- Brute force - try all digits until sudoku is solved, recursion
- Marking algorithm:

1. Mark all cells with all possible digits
2. Fill the cells with single mark
3. Fill all digits that have only one possible placement in a set (row, column, 3x3 box)
4. Repeat steps #2 & #3 until no changes are made 
   - If puzzle is solved, stop here
5. Find digits that have possible placements in single row or column of a box
   - If found, unmark these digits from the rest of the row or column
6. Find <N> cells of a set where only <N> digits have possible placement there
   - If found, unmark these digits from the rest of the row or column
7. Go to step #2

Note: With each digit solved the now conflicting marks should be erased

Controls:
Buttons:
- "Solve", "Solve Brute" - will attempt to solve the sudoku using the respective algorithm
- "Stop" - will stop solving process
- "Delete all" - deletes all digits from the grid
- "Prefill grid" - prefills the grid with preset puzzles based on "Prefill ID"
- "Solve slowly" - slows down the solving algorithm, introduces short sleep whenever and change on the grid is made
- "Prefill ID" - choose puzzle to prefill:
  - 1 - Easy
  - 2 - Medium
  - 3 - Hard
  - 4 - Very Hard #1
  - 5 - Very Hard #2
- Grid:
  - Click to select or unselect cell
  - Write a digit (1-9), use backspace or delete to erase digit
  - If cell is selected, use arrow keys to move around, borders loop around 
 
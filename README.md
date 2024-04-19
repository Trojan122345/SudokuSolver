A project created for me to better understand C++ and the SFML library.

The goal is to create an app that can solve and possibly create new sudoku.

As of now there is:
  - A writable sudoku grid - classic sudoku finalDigit grid that reacts to mouse events and when active also specific key presses (digits to write, backpase and delete to erase and arrows to move around the grid)
  - Three buttons
      - one to start the solving algorithm
      - one to erase the grid
      - one added for testing - inputs testing puzzles based on number input in the box next to it
          - #1 inputs an "Easy" puzzle
          - #2 inputs a "Medium" puzzle
          - #3 inputs a "Hard" puzzle
          - #4, default inputs "Very Hard" puzzle - this puzzle cannot be solved using simple solving strategies
  - Solving algorithm with basic solving methods and one advanced one
  - Solving attempts are animated
      - Final digits are shown as a big number
      - Possible digits are shown as smaller digits, located based on the number
    
Next goals:
  - Adding the rest of advanced solving strategies
  - Creating an GUI for creating new sudoku with several difficulty levels with help of solving algorithm
  - Optimizing and polishing code in the end

Solving algorithm (planned):
1. Mark all cells with all possible (non-conflicting) digits
2. Fill the cells where only one finalDigit is possible
3. Fill all the digits that have only one possible placement in a row/column/box
    - Loop #2 & #3 until the puzzle is complete or no cells are solved during whole iteration
4. If not full yet, do the advanced strategies
    - Loop #2, #3 & #4 until complete or no cells are solved during whole iteration
5. Guess a finalDigit and proceed to loop #2, #3 and #4 - if finalDigit is proven wrong, unmark the finalDigit and continue
6. Puzzle should be complete now

Note: with each finalDigit solved the now conflicting marks should be deleted

Advanced strategies:
1. If number is only marked in a single row/column in a box, we can unmark the number from the rest of said row/column
   - works same for 2 rows/columns across 2 boxes
2. If there are X digits marked across X cells in a set and no other digit is marked in these cells, marks of said digits can be removed from all other cells in that set
3. If X digits have X marks across X cells of a set, all other marks can be removed from these cells
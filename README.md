A project created for me to better understand C++ and the SFML library.

The goal is to create an app that can solve and possibly create new sudoku.

As of now there is:
  - a writable sudoku grid - classic sudoku finalNumber grid that reacts to mouse events and when active also specific key presses (numbers to write, backpase and delete to erase and arrows to move around the grid)
  - a button that reacts to mouse events but without functionality

Next goals:
  - Creating an algorithm to solve sudoku game based on the grid input and hooking it up to the button
  - Creating an GUI for creating new sudoku with several difficulty levels with help of solving algorithm
  - Optimizing and polishing code in the end



Solving algorithm (planned):
1. Mark all cells with all possible (non conflicting) numbers
2. Fill the cells where only one finalNumber is possible
3. Fill all the numbers that have only one possible placement in a row/column/box
    - Loop #2 & #3 until the puzzle is complete or no cells are filled during whole iteration
4. If not full yet, do the tricks
    - Loop #2, #3 & #4 until complete or no cells are filled during whole iteration
5. Guess a finalNumber and proceed to loop #2, #3 and #4 - if finalNumber is proven wrong, unmark the finalNumber and continue
6. Puzzle should be complete now

Note: with each finalNumber filled the now conflicting marks should be deleted
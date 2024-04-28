target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Button.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Object.cpp
        ${CMAKE_CURRENT_LIST_DIR}/TextBox.cpp
        ${CMAKE_CURRENT_LIST_DIR}/SolverGUI.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NumericUpDown.cpp)

add_subdirectory(numberGrid)
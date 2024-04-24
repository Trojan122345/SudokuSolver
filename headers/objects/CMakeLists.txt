target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Button.h
        ${CMAKE_CURRENT_LIST_DIR}/Object.h
        ${CMAKE_CURRENT_LIST_DIR}/TextBox.h
        ${CMAKE_CURRENT_LIST_DIR}/SolverGUI.h)

add_subdirectory(numberGrid)

include_directories(numberGrid)
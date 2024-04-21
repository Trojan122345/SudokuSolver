target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Cell.h
        ${CMAKE_CURRENT_LIST_DIR}/NineSet.h
        ${CMAKE_CURRENT_LIST_DIR}/Solver.h)

target_sources(Tests PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Cell.h
        ${CMAKE_CURRENT_LIST_DIR}/NineSet.h
        ${CMAKE_CURRENT_LIST_DIR}/Solver.h)
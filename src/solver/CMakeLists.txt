target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Cell.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NineSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Solver.cpp)

target_sources(Tests PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Cell.cpp
        ${CMAKE_CURRENT_LIST_DIR}/NineSet.cpp
        ${CMAKE_CURRENT_LIST_DIR}/Solver.cpp)
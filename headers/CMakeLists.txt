target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Core.h)

target_sources(Tests PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Core.h)

add_subdirectory(objects)
add_subdirectory(solver)
add_subdirectory(util)
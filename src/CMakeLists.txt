target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Core.cpp
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

add_subdirectory(solver)
add_subdirectory(objects)
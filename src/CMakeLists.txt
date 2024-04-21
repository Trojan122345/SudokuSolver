target_sources(SudokuSolver PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Core.cpp
        ${CMAKE_CURRENT_LIST_DIR}/main.cpp)

target_sources(Tests PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Core.cpp)

add_subdirectory(solver)
add_subdirectory(objects)
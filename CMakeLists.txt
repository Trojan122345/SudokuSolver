cmake_minimum_required(VERSION 3.24)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(SudokuSolver src/main.cpp src/Core.cpp headers/Core.h src/objects/Object.cpp headers/objects/Object.h src/objects/numberGrid/NumberGrid.cpp headers/objects/numberGrid/NumberGrid.h src/objects/numberGrid/TextBox.cpp headers/objects/numberGrid/TextBox.h src/objects/numberGrid/Button.cpp headers/objects/numberGrid/Button.h src/objects/solver/Solver.cpp headers/objects/solver/Solver.h src/objects/solver/Cell.cpp headers/objects/solver/Cell.h src/objects/solver/NineSet.cpp headers/objects/solver/NineSet.h)

add_executable(Tests Test/NineSetTests.cpp src/objects/Object.cpp headers/objects/Object.h src/objects/numberGrid/NumberGrid.cpp headers/objects/numberGrid/NumberGrid.h src/objects/numberGrid/TextBox.cpp headers/objects/numberGrid/TextBox.h src/objects/numberGrid/Button.cpp headers/objects/numberGrid/Button.h src/objects/solver/Solver.cpp headers/objects/solver/Solver.h src/objects/solver/Cell.cpp headers/objects/solver/Cell.h src/objects/solver/NineSet.cpp headers/objects/solver/NineSet.h Test/CellTests.cpp)

include_directories(headers "C:/SFML")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML COMPONENTS system window graphics REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SudokuSolver ${SFML_LIBRARIES})
    target_link_libraries(Tests ${SFML_LIBRARIES})
endif()

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

target_link_libraries(Tests gtest_main)

cmake_minimum_required(VERSION 3.24)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 17)

add_executable(SudokuSolver src/main.cpp src/Core.cpp headers/Core.h src/objects/Object.cpp headers/objects/Object.h src/objects/numberGrid/NumberGrid.cpp headers/objects/numberGrid/NumberGrid.h src/objects/numberGrid/TextBox.cpp headers/objects/numberGrid/TextBox.h)

include_directories(headers "C:/SFML")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML COMPONENTS system window graphics REQUIRED)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(SudokuSolver ${SFML_LIBRARIES})
endif()

if(WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()
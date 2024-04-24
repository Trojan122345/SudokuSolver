cmake_minimum_required(VERSION 3.24)
project(SudokuSolver)

set(CMAKE_CXX_STANDARD 17)



add_executable(SudokuSolver)
add_executable(Tests)

include_directories(
        headers
        headers/objects
        headers/solver
        headers/util
        headers/objects/numberGrid)

add_subdirectory(src)
add_subdirectory(headers)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(SudokuSolver PRIVATE sfml-graphics)
target_link_libraries(SudokuSolver PRIVATE sfml-window)
target_link_libraries(SudokuSolver PRIVATE sfml-system)

if(WIN32)
    add_custom_command(
            TARGET SudokuSolver
            COMMENT "Copy OpenAL DLL"
            PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SudokuSolver>
            VERBATIM)
endif()

install(TARGETS SudokuSolver)

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

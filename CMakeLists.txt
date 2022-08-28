cmake_minimum_required(VERSION 3.23)
project(Ableton_Programming_Task)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
#
#add_executable(Ableton_Programming_Task main.cpp parse_input.h parse_input.cpp WarpMarker.cpp WarpMarker.h)

# Your library sources go here
set(LIBRARY_SOURCES parse_input.cpp WarpMarker.cpp)
set(LIBRARY_HEADERS parse_input.h WarpMarker.h)

add_library(parse_input_library ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

# exec sources go here
set(EXEC_SOURCES main.cpp)

add_executable(Ableton_Programming_Task ${EXEC_SOURCES})
target_link_libraries(Ableton_Programming_Task parse_input_library)

# Tests
enable_testing()

# Your tests
set(TEST_SOURCES test/tests.cpp)

add_executable(unit_tests ${TEST_SOURCES})

target_link_libraries(unit_tests parse_input_library)

add_test(unit_tests unit_tests)
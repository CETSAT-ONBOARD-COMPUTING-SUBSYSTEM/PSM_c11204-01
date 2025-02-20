cmake_minimum_required(VERSION 3.0.0)
project(Lucy VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)
enable_testing()

include_directories(include src)
file(GLOB_RECURSE TARGET_SRC "src/*.cpp" "src/*.c")

add_executable(main ${TARGET_SRC})

cmake_minimum_required(VERSION 3.7)

find_package(Curses REQUIRED)
target_link_libraries(main ${CURSES_LIBRARIES})

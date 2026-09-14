cmake_minimum_required(VERSION 3.16)

project(slcxe)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(Curses REQUIRED)

add_executable(slcxe
	src/main.cpp
)

target_include_directories(slcxe PRIVATE
	include
	${CURSES_INCLUDE_DIR}
)

target_link_libraries(slcxe PRIVATE
	${CURSES_LIBRARIES}
)

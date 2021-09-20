cmake_minimum_required(VERSION 3.0)
project(ant_movements CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(RENDER "RENDER" OFF)

add_executable(ant_movements
	src/main.cpp
)

if(RENDER)
	add_definitions("-DRENDER=1")
	find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
	target_link_libraries(ant_movements
		sfml-system
		sfml-window
		sfml-graphics
	)
if(UNIX)
	target_link_libraries(ant_movements
		pthread
	)
endif()
endif()

set_property(TARGET ant_movements PROPERTY CXX_STANDARD 20)

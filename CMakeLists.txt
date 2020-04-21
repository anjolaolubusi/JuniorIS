cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(MMAS-VIS VERSION 1.0.0)

file(GLOB project_src
		"src/*.h"
		"src/*.cpp"
	)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
add_executable(
	run.o
	${project_src}
	)
target_link_libraries(run.o ${SDL2_LIBRARIES})

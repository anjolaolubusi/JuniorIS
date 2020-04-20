cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(MMAS-VIS VERSION 1.0.0)
find_package(glfw3 3.3 REQUIRED)

file(GLOB project_src
		"src/*.h"
		"src/*.cpp"
	)

add_executable(
	run.o
	${project_src}
	)


find_package(glfw3 3.3 REQUIRED)
target_link_libraries(run.o glfw)
find_package(OpenGL REQUIRED)
target_link_libraries(run.o OpenGL::GL)


cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(MMAS-VIS VERSION 1.0.0)

file(GLOB project_src
		"src/*.h"
		"src/*.cpp"
	)
set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(ImGui-SFML_DIR "<ImGui repo folder>")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(ImGui-SFML REQUIRED)
add_executable(
	run.o
	${project_src}
	)
target_link_libraries(run.o PRIVATE ImGui-SFML::ImGui-SFML)
target_include_directories(run.o PRIVATE ${include/})

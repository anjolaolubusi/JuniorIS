COMPILER = g++
C_FLAGS = -g -Wall 
EXEC = run.o
SRC_DIR = src
FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h)
TEST_FILES = src/GraphMap.h src/GraphMap.cpp src/main.cpp src/PheroKey.h src/PheroKey.cpp
compile: $(FILES)
	$(COMPILER) $(C_FLAGS) $(FILES) -o $(EXEC)

clean:
	rm -rf $(EXEC)

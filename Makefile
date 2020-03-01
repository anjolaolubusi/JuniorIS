COMPILER = g++
C_FLAGS = -g -Wall 
EXEC = run.o
SRC_DIR = src
FILES = $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/*.h)
compile: $(FILES)
	$(COMPILER) $(C_FLAGS) $(FILES) -o $(EXEC)

clean:
	rm -rf $(EXEC)

COMPILER = g++
C_FLAGS = -g -Wall
EXEC = run.o
FILES = main.cpp SmartPtr.h AntMap.h AntMap.cpp
compile: $(FILES)
	$(COMPILER) $(C_FLAGS) $(FILES) -o $(EXEC)

clean:
	rm -rf $(EXEC)

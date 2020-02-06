CC = g++
C_FLAGS = -g -Wall
EXEC = run.o
FILES = main.cpp SmartPtr.h
compile: $(FILES)
	$(CC) $(C_FLAGS) $(FILES) -o $(EXEC)

clean:
	rm -rf $(EXEC)

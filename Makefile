# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -g

# Source files
SRC = main.c

# Executable name
EXE = guish

# Rule to build the executable
$(EXE): $(SRC)
	$(CC) $(CFLAGS) -o $(EXE) $(SRC)

# Rule to run tests
test: $(EXE)
	./test_guish.sh

# Rule to clean up generated files
clean:
	rm -f $(EXE) *.o

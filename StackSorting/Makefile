# Compiler
CXX = g++
CXXFLAGS = -Wall

# Executable name
EXEC = StackSorting.exe

# Source files
SRC = StackSorting.cpp

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

# Run the executable with inputs
run: $(EXEC)
	@echo "Running $(EXEC) with multiple inputs"
	@for ((i=3; i<=9; i++)); do \
	    echo "Running with input: $$i"; \
		printf "test_%dS_NoPath.out\n%d\nm\n" $$i $$i | ./$(EXEC); \
	done

# Clean up
clean:
	rm -f $(EXEC)

.PHONY: all run clean

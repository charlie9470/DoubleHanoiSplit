# Compiler
CXX = g++
CXXFLAGS = -Wall

# Executable name
EXEC = a.out

# Source files
SRC = organizetests.cpp

# Default target
all: $(EXEC)

# Build executable
$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

# Run the executable with inputs
run: $(EXEC)
	@echo "Running $(EXEC) with multiple inputs"
	@for ((i=3; i<=9; i++)); do \
	    echo "Running with input: test_$${i}S_NoPath.out\n"; \
		printf "test_%dS_NoPath.out\n" $${i} | ./$(EXEC); \
	done

# Clean up
clean:
	rm -f $(EXEC)

.PHONY: all run clean

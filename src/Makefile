# The compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++20

# Default target to run everything
all: run

# Compile the source file
$(basename $(SRC)).o: $(SRC)
	$(CXX) $(CXXFLAGS) -c $(SRC)

# Link the object file to create the executable
$(basename $(SRC)): $(basename $(SRC)).o
	$(CXX) $(basename $(SRC)).o -o $(basename $(SRC))

# Run the executable
run: $(basename $(SRC))
	./$(basename $(SRC))
	$(MAKE) clean SRC=$(SRC)

# Clean up object and executable files
clean:
	rm -f $(basename $(SRC)).o $(basename $(SRC))

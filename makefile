# Compiler
CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Werror -Wsign-conversion -g

# Coverage flags
COVFLAGS = -fprofile-arcs -ftest-coverage

# Profiling flags
PROFFLAGS = -pg

# Valgrind flags
VALFLAGS = --leak-check=full --log-file="valgrind_log.txt"

# Source files
SRC = main.cpp Graph.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Executable
EXEC = main

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(EXEC)
	./$(EXEC) -v 5 -e 7 -s 42

# Generate code coverage report
coverage: CXXFLAGS += $(COVFLAGS)
coverage: clean $(EXEC)
	./$(EXEC) -v 5 -e 7 -s 42
	gcov $(SRC)
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory out

# Profiling with gprof
profile: CXXFLAGS += $(PROFFLAGS)
profile: clean $(EXEC)
	./$(EXEC) -v 5 -e 7 -s 42
	gprof $(EXEC) gmon.out > analysis.txt

# Memory checking with Valgrind
valgrind: $(EXEC)
	valgrind $(VALFLAGS) ./$(EXEC) -v 5 -e 7 -s 42

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC) gmon.out *.gcda *.gcno *.gcov coverage.info
	rm -rf out
	rm -f valgrind_log.txt callgrind.out.*

.PHONY: all run coverage profile valgrind clean

# Compiler
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Werror -Wsign-conversion -g -no-pie

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
all: $(EXEC) singletone hello abs4race

# Build the executable
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

singletone: $ singletone.o
	$(CXX) $(CXXFLAGS) -o $@ $^

abs4race: $ abs4race.o
	$(CXX) $(CXXFLAGS) -o $@ $^

hello: $ hello.o
	$(CXX) $(CFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

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

# Memory checking with Valgrind (memcheck)
valgrind_memcheck: $(EXEC)
	valgrind $(VALFLAGS) ./$(EXEC) -v 5 -e 7 -s 42

# Generate call graph with Valgrind's callgrind tool
valgrind_callgrind: $(EXEC)
	valgrind --tool=callgrind --callgrind-out-file=custom_callgrind.out ./$(EXEC) -v 5 -e 7 -s 42
	kcachegrind custom_callgrind.out

# Clean up generated files
clean:
	rm -f $(OBJ) $(EXEC) hello.o hello singletone singletone.o abs4race.o abs4race gmon.out *.gcda *.gcno *.gcov coverage.info 
	rm -rf out
	rm -f valgrind_log.txt callgrind.out.*

.PHONY: all run coverage profile valgrind callgrind clean

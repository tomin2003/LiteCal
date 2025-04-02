# Variables
CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -g -DMEMTRACE
OBJ = string.o calendar.o datetime.o memtrace.o test.o
HEADERS = string.h calendar.h event.h memtrace.h datetime.h
TARGET = test

# Default rule
all: $(TARGET)

# Linking step
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilation step (fixed file extensions and dependencies)
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule (removes object files and executable)
clean:
	rm -f $(OBJ) $(TARGET)

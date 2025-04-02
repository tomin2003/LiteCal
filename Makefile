# Változók
CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -g -DMEMTRACE
OBJ = string.o calendar.o datetime.o memtrace.o test.o
HEADERS = string.h calendar.h event.h memtrace.h datetime.h
TARGET = test

# Alapértelmezett
all: $(TARGET)

# Linkelés lépések
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Fordítási lépések
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Takarítás
clean:
	rm -f $(OBJ) $(TARGET)

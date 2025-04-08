# Változók
CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -g -DMEMTRACE
HEADERS = memtrace.h except.h string.h calendar.h date.h time.h event.h datetime.h
OBJ = memtrace.o string.o calendar.o date.o time.o event.o test.o
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

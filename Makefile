# Változók
CXX = g++
CXXFLAGS = -pedantic -Wall -Werror -g -DMEMTRACE
HEADERS = memtrace.h except.h string.h calendar.h date.h time.h event.h datetime.h
OBJ = memtrace.o string.o calendar.o date.o time.o event.o

# Teszteset fordítása a "test" vezérlővel (anélkül a program rendesen lefordul)
ifneq ($(MAKECMDGOALS),test)
  HEADERS += menu.h
  OBJ += menu.o main.o
  TARGET = calendar
else
  OBJ += test.o
  TARGET = test
endif

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
CXX := g++
CXXFLAGS := -std=c++17 -pthread -Wall -Wextra -Wpedantic
TARGET := my-dining

# starter: main.cpp compiles as a placeholder until implementations exist.
# integration needed: replace with:
# SOURCES := main.cpp dining.cpp peterson_lock.cpp tournament_tree_lock.cpp
SOURCES := main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES) dining.h
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean

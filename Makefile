# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++17
CXXDEBUG = -g3 -O0
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Targets
GAME_TARGET = game
TEST_TARGET = test
DEBUG_TARGET = game_debug

# Source files
GAME_SRC = main.cpp unit.cpp entity.cpp
TEST_SRC = vibecoded.cpp

# Object files
GAME_OBJ = $(GAME_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Default target
all: $(GAME_TARGET)

# Build main game
$(GAME_TARGET): $(GAME_OBJ)
	$(CXX) $(GAME_OBJ) -o $(GAME_TARGET) $(LIBS)

# Build debug version
debug: $(GAME_OBJ)
	$(CXX) $(GAME_OBJ) -o $(DEBUG_TARGET) $(LIBS) $(CXXDEBUG)

# Build test program
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(TEST_OBJ) -o $(TEST_TARGET) $(LIBS)

# Generic rule for .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean everything
clean:
	rm -f $(GAME_OBJ) $(TEST_OBJ) $(GAME_TARGET) $(DEBUG_TARGET) $(TEST_TARGET)

.PHONY: all clean debug

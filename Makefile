# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I"./libs/" -DSOL_ALL_SAFETIES_ON=1 `pkg-config --cflags lua`
LDFLAGS = `pkg-config --cflags --libs sdl2 lua` -lSDL2_image -lSDL2_mixer -lSDL2_ttf

# Add more libraries as you progress:
# LDFLAGS = `pkg-config --cflags --libs sdl2 SDL2_image SDL2_mixer lua`

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Output executable
TARGET = gameengine

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

# Run the game
run: $(TARGET)
	./$(TARGET)

# Clean build artifacts
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all run clean

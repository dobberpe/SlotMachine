CXX = g++
CXXFLAGS = -std=c++20 -Wall -I SFML-3.0.0/include
LDFLAGS = -L SFML-3.0.0/lib -lsfml-graphics -lsfml-window -lsfml-system -Wl,-rpath,$(PWD)/SFML-3.0.0/lib

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)

SOURCES = $(shell find $(SRC_DIR) -type f -name "*.cpp")
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

TARGET = $(BIN_DIR)/slot_machine

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Building executable: $(TARGET)"
	@mkdir -p $(BIN_DIR)
	@$(CXX) $^ -o $@ $(LDFLAGS)
	@echo "Build completed!"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling: $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean: clean-objects
	@echo "Cleaning all build files..."
	@rm -rf $(BUILD_DIR)
	@echo "Clean completed!"

clean-objects:
	@echo "Removing object files and empty directories..."
	@if [ -d "$(OBJ_DIR)" ]; then find $(OBJ_DIR) -type f -name "*.o" -delete; fi
	@if [ -d "$(OBJ_DIR)" ]; then find $(OBJ_DIR) -type d -empty -delete; fi
	@echo "Object files removed!"

re: clean $(TARGET)
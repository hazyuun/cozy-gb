CXX = g++
LDFLAGS = -lglfw -lGL -lGLEW
INCLUDE = -Isrc -I.
CCFLAGS = -Wno-write-strings -g -O2

SRC = $(shell find ./src -name "*.cpp")
OBJ = $(patsubst ./src/%.cpp, ./obj/%.o, $(SRC))

.phony: all
all: dirs $(OBJ)
	@echo Linking object files ..
	@$(CXX) $(OBJ) -o bin/cozy-gb $(CCFLAGS) $(INCLUDE) $(LDFLAGS)

.phony: dirs
dirs:
	@mkdir -p bin obj

obj/%.o: src/%.cpp
	@echo [CXX] $@
	@$(CXX) -c $< -o $@ $(CCFLAGS) $(INCLUDE) $(LDFLAGS)

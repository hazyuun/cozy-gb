CXX = g++
LDFLAGS = -lglfw -lGL -lGLEW
INCLUDE = -Isrc -I. -Iimgui
CCFLAGS = -Wno-write-strings -g -O2

SRC = $(shell find ./src -name "*.cpp")
OBJ = $(patsubst ./src/%.cpp, ./obj/%.o, $(SRC))

.phony: all
all: $(OBJ)
	@echo Linking object files ..
	@$(CXX) $(OBJ) imgui/imgui.a -o bin/niou $(CCFLAGS) $(INCLUDE) $(LDFLAGS)


obj/%.o: src/%.cpp
	@echo [CXX] $@
	@$(CXX) -c $< -o $@ $(CCFLAGS) $(INCLUDE) $(LDFLAGS)

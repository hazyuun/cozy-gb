CXX = g++
LDFLAGS = -lglfw -lGL -lGLEW

all:
	$(CXX) -Wno-write-strings -g src/*.cpp -o bin/niou $(LDFLAGS) 
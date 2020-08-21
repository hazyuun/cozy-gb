CXX = g++
LDFLAGS = -lglfw -lGL -lGLEW

all:
	$(CXX) -Wno-write-strings -g -O2 src/*.cpp -o bin/niou $(LDFLAGS) 
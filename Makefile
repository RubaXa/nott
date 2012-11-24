CXX = g++47
CXXFLAGS = -Wall -std=c++11 -O2 -o
FILE = nott

all: build

build:
	$(CXX) $(CXXFLAGS) $(FILE) $(FILE).cpp && ./$(FILE)

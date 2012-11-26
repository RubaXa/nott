CXX = clang++
CXXFLAGS = -Wall -std=c++11 -stdlib=libc++ -O2 -o
FILE = nott

all: build

build:
	$(CXX) $(CXXFLAGS) $(FILE) $(FILE).cpp && ./$(FILE)

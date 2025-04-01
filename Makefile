# Compiler and Flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./src -I./src/hal -I./tests

# Targets to build
TARGETS = ebikeClient generateEBikeFile

.PHONY: all clean

all: $(TARGETS)

# Build the main eBike client executable.
# Assumes ebikeClient.cpp and GPSSensor.h are in src/ and CSVHALManager.h is in src/hal.
ebikeClient: src/ebikeClient.cpp src/GPSSensor.h src/hal/CSVHALManager.h
	$(CXX) $(CXXFLAGS) -o ebikeClient src/ebikeClient.cpp

# Build the generateEBikeFile utility.
# Assumes generateEBikeFile.cpp is in src/util.
generateEBikeFile: src/util/generateEBikeFile.cpp
	$(CXX) $(CXXFLAGS) -o generateEBikeFile src/util/generateEBikeFile.cpp

clean:
	rm -f ebikeClient generateEBikeFile

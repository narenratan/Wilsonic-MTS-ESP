CXX = g++
CXXFLAGS = -std=c++17 -I../Source -I. -Wall -Wextra
TARGET = test_wilsonicmath

all: $(TARGET)

$(TARGET): test_wilsonicmath.cpp ../Source/WilsonicMath.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f $(TARGET)

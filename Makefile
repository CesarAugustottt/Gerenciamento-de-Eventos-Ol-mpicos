CXX = g++
CXXFLAGS = -std=c++17 -Wall -Werror

TARGET = bin/gestao_olimpica

all:
	mkdir -p bin
	$(CXX) $(CXXFLAGS) src/*.cpp -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf bin
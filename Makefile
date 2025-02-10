main: main.cpp
	g++ main.cpp -o ./build/main -Wall -Wextra -Iinclude -std=c++17 -lraylib -lm -ldl -lpthread -lGL

clean:
	rm -f ./build/main

output: game
	g++ -std=c++11 main.cpp -o game -lSDL2 -lSDL2_image -lGLEW -framework OpenGL

game: main.cpp

clean:
	rm *.o
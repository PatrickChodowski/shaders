output: game
	g++ main.cpp -o game  -lSDL2 -lSDL2_image -lGL -lGLEW

game: main.cpp

clean: rm *.o
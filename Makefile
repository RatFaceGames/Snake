all:
	g++ -I/usr/include/GL -I/usr/include/SDL2 *.cpp -lSDL2 -lGLEW -lSDL -lGL
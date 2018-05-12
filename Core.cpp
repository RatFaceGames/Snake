/* 
	Program to play snake using OpenGL and SDL
	Nicolas LaCognata
	Ben Caldwell
*/

//Libraries
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

//C++ headers
#include <iostream>
#include <utility>
#include <string>

//Classes
#include "Renderer.h"

#define PROGRAM_NAME "SDL WITH OPENGL RENDERING CONTEXT"

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

//Initialization functions
void input();
void update();
void draw();

int main(int argc, char *argv[]) {
	//init();
	Renderer renderSystem(PROGRAM_NAME, 512, 512);

	//Example of messing with window.
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(renderSystem.getWindow());


	//Loop control variables
	SDL_Event input;
	bool quit = false;
	
	Uint32 startClock = 0;
	Uint32 deltaClock = 0;
	Uint32 currentFPS = 0;

	//Main loop
	//TODO: Count and control frame rate.
	while (!quit) {
		while (SDL_PollEvent(&input) != 0) {
			if (input.type == SDL_QUIT)
				quit = true;
		}
	}
	//shutdown();
	return 0;
}
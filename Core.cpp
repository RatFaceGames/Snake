/* 
	Program to play snake using OpenGL and SDL
	Nicolas LaCognata
	Ben Caldwell

	TODO:
		Learn how to draw a fucking triangle.
			https://www.youtube.com/watch?v=Dyue3MzJDss&index=4&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY
			https://learnopengl.com/Getting-started/Hello-Triangle
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
#include "RenderingSystem.h"

#define PROGRAM_NAME "SDL WITH OPENGL RENDERING CONTEXT"

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

//Initialization functions
void input();
void update();
void draw(unsigned int vertexBuffer);

int main(int argc, char *argv[]) {
	//init();
	RenderingSystem renderSystem(PROGRAM_NAME, 640, 480);

	//Example of messing with window.
	/*
	glClearColor(0.5, 0, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(renderSystem.getWindow());
	*/
	//Loop control variables
	SDL_Event input;
	bool quit = false;
	
	//Main loop
	while (!quit) {
		while (SDL_PollEvent(&input) != 0) {
			if (input.type == SDL_QUIT)
				quit = true;
		}
		
	}
	//shutdown();
	return 0;
}
void draw(unsigned int vertexBuffer) { //TEMP FUNCTIONALITY, DRAW A TRIANGLE.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnableVertexAttribArray(0);
}
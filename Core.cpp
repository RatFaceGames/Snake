/*
		Program to play snake using OpenGL and SDL
		Nicolas LaCognata
		Ben Caldwell

		TODO:
				Learn how to draw a fucking triangle.
				GLEW isn't initializing right.
						https://www.youtube.com/watch?v=Dyue3MzJDss&index=4&list=PLRwVmtr-pp06qT6ckboaOhnm9FxmzHpbY
						https://learnopengl.com/Getting-started/Hello-Triangle
*/

// Libraries
#include <GL/glew.h>
#include <SDL.h>

// C++ headers
#include <iostream>
#include <string>
#include <utility>

// Classes
#include "RenderingSystem.h"

#define PROGRAM_NAME "SDL WITH OPENGL RENDERING CONTEXT"

// Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

// Initialization functions
void input();
void update();
void draw(unsigned int vertexBuffer);

int main(int argc, char *argv[]) {
	RenderingSystem renderSystem(PROGRAM_NAME, 640, 480);
	SDL_Event input;
	bool quit = false;

	// Sample triangle
	float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f,
						0.0f,  0.0f,  0.5f, 0.0f};
	GLuint VertexArrayObject;  // VAO's hold one or more vertex buffers for a
							   // single object
	GLuint VertexBufferObject; // VBO's are memory buffers fed to the GPU for
							   // processing. Can hold position data, color
							   // data, etc.

	// Init VAO
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);

	// Init VBO
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
				 GL_STATIC_DRAW); // feed it vertex array

	// Vertex shader shit
	const char *vertexShaderSource =
		"#version 430 core\n"
		"layout(location = 0) in vec3 aPos;\n"
		"void main(){\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\n";

	// Colors triangle purple
	const char *fragmentShaderSource = "#version 430 core\n"
									   "out vec3 color;\n"
									   "void main(){\n"
									   "	color = vec3(1,0,1);\n"
									   "}\n";
	GLuint programID =
		renderSystem.loadShaders(vertexShaderSource, fragmentShaderSource);
	// Main loop
	while (!quit) {
		while (SDL_PollEvent(&input) != 0) {
			if (input.type == SDL_QUIT) {
				quit = true;
				continue;
			}

			glClear(GL_COLOR_BUFFER_BIT |
					GL_DEPTH_BUFFER_BIT); // Clear back buffer
			glUseProgram(programID);

			// Enable vertex array
			glEnableVertexAttribArray(0);
			// Ensure buffer bound
			glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
			// Set attribures
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
			// draw
			glDrawArrays(
				GL_TRIANGLES, 0,
				3); // Starting from vertex 0; 3 vertices total -> 1 triangle
			// Disable vertex array
			glDisableVertexAttribArray(0);

			SDL_GL_SwapWindow(
				renderSystem
					.getWindow()); // Swaps back buffer we drew on into window.
		}
	}
	// shutdown();
	return 0;
}
void draw(unsigned int vertexBuffer) { // TEMP FUNCTIONALITY, DRAW A TRIANGLE.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glEnableVertexAttribArray(0);
}

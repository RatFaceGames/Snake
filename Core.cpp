#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <iostream>
#include <utility>
#include <string>

#define PROGRAM_NAME "SDL WITH OPENGL RENDERING CONTEXT"

//Constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int FPS = 60;

//Globals
static SDL_Window *window = nullptr;
static SDL_GLContext renderContext;

void init(); //Wrapper for initSDL and initGL
void initSDL();
void initGL();
void update();
void render();
void shutdown();

void SDLdie(const char* msg);
void GLEWdie(const char* msg, int status);

int main(int argc, char *argv[]) {
	init();
	
	//Loop control variables
	SDL_Event input;
	bool quit = false;
	unsigned int frameStart;
	unsigned int frameEnd;
	unsigned int frameRate;
	
	//Main loop
	//TODO: Count and control frame rate.
	while (!quit) {
		frameStart = SDL_GetTicks();

		while (SDL_PollEvent(&input) != 0) {
			if (input.type == SDL_QUIT)
				quit = true;
		}
		frameEnd = SDL_GetTicks();
	}
	shutdown();
	return 0;
}

void initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDLdie("SDL failed to initialize");
	//Version setup
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	//Double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	//Windowsetup
	window = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  SCREEN_WIDTH, SCREEN_HEIGHT, 
							  SDL_WINDOW_OPENGL);

	if (window == nullptr)
		SDLdie("Error: Window not created");

	renderContext = SDL_GL_CreateContext(window);
	
	return;
}
void init() {
	std::cout << "Begin initialization\n";
	initSDL();
	initGL();



	std::cout << "\tUsing GLEW version: " << glewGetString(GLEW_VERSION) << "\n";
	std::cout << "\tUsing OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}
void initGL() {
	int status = glewInit();
	if (status != GLEW_OK)
		GLEWdie("Error: GLEW failed to initialize", status);
	
	//Initialize color buffer to black plane
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);	//Swaps buffer into window. "draw"
}
void GLEWdie(const char *msg, int status) {
	std::cerr << msg << " " << glewGetErrorString(status);
}
void SDLdie(const char* msg) {
	std::cerr << msg << " " << SDL_GetError();
	SDL_Quit();
	exit(EXIT_FAILURE);
}
void shutdown() {
	SDL_GL_DeleteContext(renderContext);
	SDL_Quit();
}
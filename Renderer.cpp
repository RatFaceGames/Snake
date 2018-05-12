#include "Renderer.h"

#include <iostream>
#include <string>

Renderer::Renderer(std::string programName, int screenWidth, int screenHeight){
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->programName = programName;
	init();
	return;
}
SDL_Window* Renderer::getWindow() {
	return window;
}
SDL_GLContext* Renderer::getRenderingContext() {
	return &renderContext;
}
Renderer::~Renderer(){
	SDL_GL_DeleteContext(renderContext);
	SDL_Quit();
}

void Renderer::init() {
	std::cout << "Renderer Initialized" << std::endl; 
	initSDL();
	initGL();
	
	std::cout << "\tUsing GLEW version: " << glewGetString(GLEW_VERSION) << "\n";
	std::cout << "\tUsing OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void Renderer::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDLdie("SDL failed to initialize");
	//Version setup
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	//Double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetSwapInterval(1);

	//Windowsetup
	window = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenWidth, screenHeight,
		SDL_WINDOW_OPENGL);

	if (window == nullptr)
		SDLdie("Error: Window not created");

	renderContext = SDL_GL_CreateContext(window);

	return;
}

void Renderer::initGL() {
	int status = glewInit();
	if (status != GLEW_OK)
		GLEWdie("Error: GLEW failed to initialize", status);

	//Initialize color buffer to black plane
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	SDL_GL_SwapWindow(window);	//Swaps buffer into window. "draw"
}

void Renderer::SDLdie(const char* msg) {
	std::cerr << msg << " " << SDL_GetError();
	SDL_Quit();
	exit(EXIT_FAILURE);
}
void Renderer::GLEWdie(const char *msg, int status) {
	std::cerr << msg << " " << glewGetErrorString(status);
}
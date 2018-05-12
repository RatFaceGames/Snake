#pragma once
/*
	Sets up and provides handles to SDL and OpenGL contexts.
*/
//Libraries
#include <SDL.h>
#include <GL\glew.h>
#include <SDL_opengl.h>

#include <string>
class Renderer{
private:
	int screenWidth;
	int screenHeight;
	std::string programName;
	SDL_Window *window;
	SDL_GLContext renderContext;

public:
	Renderer(std::string programName, int screenWidth, int screenHeight);
	SDL_Window *getWindow();
	SDL_GLContext* getRenderingContext();
	~Renderer();

private:
	void init();
	void initSDL();
	void initGL();

	void SDLdie(const char* msg);
	void GLEWdie(const char *msg, int status);

};


#include "RenderingSystem.h"

#include <iostream>
#include <string>
#include <vector>

RenderingSystem::RenderingSystem(std::string programName, int screenWidth, int screenHeight){
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
	this->programName = programName;
	init();
	return;
}
SDL_Window* RenderingSystem::getWindow() {
	return window;
}
SDL_GLContext* RenderingSystem::getRenderingContext() {
	return &renderContext;
}
RenderingSystem::~RenderingSystem(){
	SDL_GL_DeleteContext(renderContext);
	SDL_Quit();
}

void RenderingSystem::init() {
	initSDL();
	initGL();
	
	std::cout << "Renderer Initialized" << std::endl; 
	std::cout << "\tUsing GLEW version: " << glewGetString(GLEW_VERSION) << "\n";
	std::cout << "\tUsing OpenGL version: " << glGetString(GL_VERSION) << std::endl;
}

void RenderingSystem::initSDL() {
	//Init SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		SDLdie("SDL failed to initialize");
	
	//Window creation
	window = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		screenWidth, screenHeight,
		SDL_WINDOW_OPENGL);

	if (window == nullptr)
		SDLdie("Error: Window not created");
	
	//OpenGL version selection
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	renderContext = SDL_GL_CreateContext(window);
	if (renderContext == nullptr)
		std::cout << "FUCK" << std::endl;

	SDL_GL_MakeCurrent(window, renderContext);
	return;
}

void RenderingSystem::initGL() {
	glewExperimental = GL_TRUE;
	GLenum GLEWstatus = glewInit();
	if (GLEWstatus != GLEW_OK)
		GLEWdie("Error: GLEW failed to initialize", GLEWstatus);

	return;
}
GLuint RenderingSystem::loadShaders(const char * vertexShader, const char * fragmentShader) {
	//MODIFIED FROM http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
	
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling vertex shader:\n";
	
	glShaderSource(VertexShaderID, 1, &vertexShader, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		std::cout << &VertexShaderErrorMessage[0] << "\n";
	}

	// Compile Fragment Shader
	std::cout << "Compiling fragment shader  %s\n";
	
	glShaderSource(FragmentShaderID, 1, &fragmentShader, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		std::cout << &FragmentShaderErrorMessage[0] << "\n";
	}

	// Link the program
	std::cout << "Linking program\n";
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << &ProgramErrorMessage[0] << "\n";
	}

	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

void RenderingSystem::SDLdie(const char* msg) {
	std::cerr << msg << " " << SDL_GetError();
	SDL_Quit();
	exit(EXIT_FAILURE);
}
void RenderingSystem::GLEWdie(const char *msg, int status) {
	std::cerr << msg << " " << glewGetErrorString(status);
}
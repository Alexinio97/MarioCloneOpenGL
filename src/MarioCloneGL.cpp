#pragma once

#include <iostream>
#include "includes/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "includes/Game.h"
/*Name of the entry file needs to match the one in cmake in order to get the cmakelists view in visual studio*/

void CalculateFPS(GLFWwindow* window);
void GLAPIENTRY OpenGLDebugMessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
);

int main() {
	Logger FreshLoger{};

	const int width = 1920;
	const int height = 1080;
	if (!glfwInit())
	{
		FreshLoger.LogError("Cannot initiate glfw!");
		return -1;
	}	
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);



	GLFWwindow* GLWindow;
	GLWindow = glfwCreateWindow(width, height, "Mario", NULL, NULL);

	if (!GLWindow)
	{
		FreshLoger.LogError("Window was null!");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(GLWindow); // Initialize GLEW
	gladLoadGL();
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		FreshLoger.LogError("Failed to initialize GLAD");
		return -1;
	}
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDebugMessageCallback(OpenGLDebugMessageCallback, __FILE__);
	
	Game MarioGame(width, height, FreshLoger);

	glViewport(0, 0, width, height);

	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	while (!glfwWindowShouldClose(GLWindow)) 
	{
		CalculateFPS(GLWindow);
		auto currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		MarioGame.OnUpdate(deltaTime);
		MarioGame.OnRender(deltaTime);		
		glfwSwapBuffers(GLWindow);
		glfwPollEvents();
	}
	FreshLoger.LogInformation("Test log!");

	glfwTerminate();
	return 0;
}

void GLAPIENTRY OpenGLDebugMessageCallback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam
)
{
	std::cerr << "OpenGL Debug Message:\n";
	std::cerr << "Source: " << source << "\n";
	std::cerr << "Type: " << type << "\n";
	std::cerr << "ID: " << id << "\n";
	std::cerr << "Severity: " << severity << "\n";
	std::cerr << "Message: " << message << "\n";

	if (userParam) {
		const char* file = static_cast<const char*>(userParam);
		std::cerr << "Triggered by: " << file << "\n";
	}
	std::cerr << std::endl;
}

void CalculateFPS(GLFWwindow* window)
{
	// Get the current time in seconds since GLFW was initialized
	static double previousTime = glfwGetTime();
	static int frameCount = 0;

	double currentTime = glfwGetTime();
	double elapsedTime = currentTime - previousTime;

	if (elapsedTime >= 1.0f)
	{		
		double fps = frameCount / elapsedTime;

		std::ostringstream titleBuffer;
		titleBuffer.precision(1);
		titleBuffer << std::fixed
			<< "Mario" << "    "
			<< "FPS: " << fps;

		glfwSetWindowTitle(window, titleBuffer.str().c_str());

		previousTime = currentTime;
		frameCount = 0;
	}

	frameCount++;
}

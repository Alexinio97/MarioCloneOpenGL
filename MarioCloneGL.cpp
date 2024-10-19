#pragma once

#include <iostream>
#include "Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "Game.h"
/*Name of the entry file needs to match the one in cmake in order to get the cmakelists view in visual studio*/

void CalculateFPS(GLFWwindow* window);

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
	
	Game MarioGame(width, height, FreshLoger);

	double deltaTime = 0.0f;
	double lastFrame = 0.0f;

	while (!glfwWindowShouldClose(GLWindow)) 
	{
		CalculateFPS(GLWindow);
		auto currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
				
		glfwPollEvents();		
		
		MarioGame.OnUpdate(deltaTime);
		glClear(GL_CLEAR_BUFFER);
		glfwSwapBuffers(GLWindow);
	}
	FreshLoger.LogInformation("Test log!");
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

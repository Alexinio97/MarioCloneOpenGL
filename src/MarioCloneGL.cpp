#pragma once

#include <iostream>
#include "includes/Logger.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <sstream>
#include "includes/Game.h"
#include "includes/Input/Input.h"

/*Name of the entry file needs to match the one in cmake in order to get the cmakelists view in visual studio*/

void CalculateFPS(GLFWwindow* window);
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

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

	glfwSetKeyCallback(GLWindow, KeyCallback);
	
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
	FreshLoger.LogInformation("Closing app!");	

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
	// ignore non-significant error/warning codes
	if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

	std::cout << "---------------" << std::endl;
	std::cout << "Debug message (" << id << "): " << message << std::endl;

	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
	case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
	} std::cout << std::endl;

	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
	case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
	case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
	case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
	case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
	case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
	} std::cout << std::endl;

	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
	case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
	} std::cout << std::endl;
	std::cout << std::endl;
}

void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, 1);
		return;
	}

	if (action == GLFW_PRESS)
	{
		Input::Keys[key] = true;
	}
	else if (action == GLFW_RELEASE && Input::Keys[key])
	{
		Input::Keys[key] = false;
	}

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

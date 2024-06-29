#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "Renderer.h"

class Application
{
public:
	Application(const int width, const int height, const char* title);
	~Application();

	void Update();

private:
	GLFWwindow* m_Window;
	Renderer renderer;
};
#include "Application.h"
#include <iostream>


Camera cam;

void mouse_callback(GLFWwindow* m_Window, double xpos, double ypos)
{
	cam.mouse_callback(m_Window, xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow* m_Window, int width, int height)
{
	glViewport(0, 0, width, height);
	cam.setAspectRatio((float)width / height);
}


Application::Application(const int width, const int height, const char* title)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (m_Window == NULL)
	{
		std::cout << "Error while creating Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_Window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glViewport(0, 0, width, height);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glfwSetCursorPosCallback(m_Window, mouse_callback);
	glfwSetFramebufferSizeCallback(m_Window, framebuffer_size_callback);

	renderer.Init();
}

Application::~Application()
{
	glfwDestroyWindow(m_Window);
	glfwTerminate();
}

void Application::Update()
{
	while (!glfwWindowShouldClose(m_Window))
	{
		cam.update(m_Window);
		renderer.Update();
		renderer.Draw(m_Window, cam.getProjMatrix(), cam.getViewMatrix());
	}
}

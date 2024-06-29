#include "Renderer.h"

void Renderer::Init()
{
	Texture default_texture("res/textures/tex.png");
	Shader default_shader("res/shaders/obj.frag", "res/shaders/obj.vert");

	m_cubes.emplace(glm::vec3(0,0,-5), Cube(default_shader, default_texture));
}

void Renderer::Update()
{

}

void Renderer::Draw(GLFWwindow* window, glm::mat4 proj, glm::mat4 view)
{
	glClearColor(0.05f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& cube : m_cubes)
	{
		cube.second.Draw(proj, view, cube.first);
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}
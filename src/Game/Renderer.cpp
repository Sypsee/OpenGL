#include "Renderer.h"

void Renderer::Init()
{
	m_chunks.emplace(glm::vec3(0, 0, -5), Chunk(glm::vec3(0, 0, -5), glm::vec3(5, 5, 5)));
}

void Renderer::Update()
{

}

void Renderer::Draw(GLFWwindow* window, Camera cam)
{
	glClearColor(0.05f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& chunk : m_chunks)
	{
		chunk.second.Draw(cam.getProjMatrix(), cam.getViewMatrix(), cam.getPosition());
	}

	glfwSwapBuffers(window);
	glfwPollEvents();
}
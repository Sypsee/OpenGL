#include "Renderer.h"

void Renderer::Init()
{
	skybox = new Skybox("res/textures/skybox", "./res/shaders/skybox.frag", "./res/shaders/skybox.vert");
	Shader shader("res/shaders/obj.frag", "res/shaders/obj.vert");
	Texture texture("res/textures/tex.png");
	monkey = new Model("res/models/monkey.obj", shader, texture);
}

void Renderer::Update()
{

}

void Renderer::Draw(GLFWwindow* window, Camera cam)
{
	glClearColor(0.05f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skybox->Draw(cam.getProjMatrix(), cam.getViewMatrix());
	monkey->Draw(cam.getProjMatrix(), cam.getViewMatrix(), cam.getPosition(), glm::vec3(0, 0, 0), 0.f, glm::vec3(5.f));

	glfwSwapBuffers(window);
	glfwPollEvents();
}

Renderer::~Renderer()
{
	delete skybox;
	delete monkey;
}
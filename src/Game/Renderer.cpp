#include "Renderer.h"

void Renderer::Init()
{
	skybox = new Skybox("res/textures/skybox", "./res/shaders/skybox.frag", "./res/shaders/skybox.vert");
	light = new Light(lightPos);
	Shader sphereShader("res/shaders/sphere.frag", "res/shaders/obj.vert");
	Shader planeShader("res/shaders/water.frag", "res/shaders/water.vert");
	Texture texture("res/textures/tex.png");
	models.push_back(Model("res/models/sphere.obj", sphereShader, texture));
	models.push_back(Model("res/models/plane.obj", planeShader, texture));
}

void Renderer::Update()
{
	light->lightPos = lightPos;
}

void Renderer::Draw(GLFWwindow* window, Camera cam)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	glClearColor(0.05f, 0.15f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ImGui::Begin("Debug Window");
	ImGui::Text("Debug Menu");
	ImGui::DragFloat3("Light Pos", glm::value_ptr(lightPos), .1f);

	skybox->Draw(cam.getProjMatrix(), cam.getViewMatrix());
	
	light->bindFrameBuffer();
	light->bindDepthTex();

	for (int i = 0; i < models.size(); i++)
	{
		std::string name = "Model ";
		name += std::to_string(i);
		name += " Pos";
		ImGui::DragFloat3(name.c_str(), glm::value_ptr(modelPos[i]), .1f);

		models[i].lightPos = light->lightPos;
		models[i].lightSpaceMatrix = light->getLightSpaceMat();
		models[i].Draw(cam.getProjMatrix(), cam.getViewMatrix(), cam.getPosition(), modelPos[i], 0, glm::vec3(1.f));
	}

	light->unBindFrameBuffer();

	ImGui::End();
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	glfwSwapBuffers(window);
	glfwPollEvents();
}

Renderer::~Renderer()
{
	delete skybox;
	delete light;
}
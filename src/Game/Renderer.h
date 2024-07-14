#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>

#include "Camera.h"
#include "Skybox.h"
#include "Model.h"
#include "Light.h"


class Renderer
{

public:
	void Init();
	void Update();
	void Draw(GLFWwindow* window, Camera cam);

	~Renderer();

private:
	Skybox* skybox;
	Light* light;
	std::vector<Model> models;

	std::vector<glm::vec3> modelPos = {
		glm::vec3(0,0,0),
		glm::vec3(0,-1,0),
	};

	glm::vec3 lightPos = glm::vec3(5,5,1);
};
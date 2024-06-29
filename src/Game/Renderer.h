#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/hash.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <string>

#include "Cube.h"


class Renderer
{

public:
	void Init();
	void Update();
	void Draw(GLFWwindow* window, glm::mat4 proj, glm::mat4 view);

private:
	std::unordered_map<glm::vec3, Cube> m_cubes;
};
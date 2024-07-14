#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <iostream>

#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

class Model
{
public:
	Model(const char* path, Shader shader, Texture texture);
	void Draw(glm::mat4 proj, glm::mat4 view, glm::vec3 camPos, glm::vec3 pos, float rotation = 0.f, glm::vec3 scale = glm::vec3(1.f));

	glm::mat4 lightSpaceMatrix;
	glm::vec3 lightPos;

private:
	std::vector<glm::vec3> v;
	std::vector<glm::vec3> vn;
	std::vector<glm::vec2> vt;

	std::vector<float> vertices;

	unsigned int VAO;
	Shader m_Shader;
	Texture m_Texture;
	Texture m_CubemapTex;
};
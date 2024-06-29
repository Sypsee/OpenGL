#pragma once

#include <glm/glm.hpp>

#include "Shader.h"
#include "Texture.h"
#include "VertexBuffer.h"


class Cube
{
public:
	Cube(Shader shader, Texture texture);

	void Draw(glm::mat4 proj, glm::mat4 view, glm::vec3 pos, float rotation = 0.f, glm::vec3 scale = glm::vec3(1.f));

private:
	unsigned int VAO;

	Shader m_shader;
	Texture m_texture;
};
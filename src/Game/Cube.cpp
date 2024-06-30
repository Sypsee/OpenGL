#include "Cube.h"

bool isFirst = false;

Cube::Cube(Shader shader, Texture texture)
	:m_shader(shader), m_texture(texture)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}

void Cube::AddFace(BlockFaceType blockFaceType)
{
	switch (blockFaceType)
	{
	case TOP:
		for (int i = 0; i < 8 * 6; i++)
		{
			m_vertexData.emplace_back(frontFace[i]);
		}
		break;
	case BOTTOM:
		for (int i = 0; i < 8 * 6; i++)
		{
			m_vertexData.emplace_back(bottomFace[i]);
		}
		break;
	case RIGHT:
		for (int i = 0; i < 8 * 6; i++)
		{
			m_vertexData.emplace_back(rightFace[i]);
		}
		break;
	case LEFT:
		for (int i = 0; i < 8 * 6; i++)
		{
			m_vertexData.emplace_back(leftFace[i]);
		}
		break;
	case FRONT:
		for (int i = 0; i < 8 * 6; i++)
		{
			m_vertexData.emplace_back(frontFace[i]);
		}
		break;
	case BACK:
		for (int i = 0; i < 8 * 6; i++)
		{
			m_vertexData.emplace_back(backFace[i]);
		}
		break;
	default:
		break;
	}
}

void Cube::CreateVertexBuffer()
{
	if (isFirst) return;

	isFirst = true;
	glBindVertexArray(VAO);

	VBO = new VertexBuffer(&m_vertexData[0], m_vertexData.size() * sizeof(float));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); // normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // uvs
	glEnableVertexAttribArray(2);
}



void Cube::Draw(glm::mat4 proj, glm::mat4 view, glm::vec3 camPos, glm::vec3 pos, float rotation, glm::vec3 scale)
{
	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.5f, 0.5f));

	m_texture.Bind();
	m_shader.Bind();
	m_shader.setMat4("proj", proj);
	m_shader.setMat4("view", view);
	m_shader.setMat4("model", model);
	m_shader.setVec3("viewPos", camPos);
	m_shader.setI("ourTexture", 0);

	glBindVertexArray(VAO);
	VBO->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 36);
	VBO->UnBind();
	glBindVertexArray(0); // Unbinding it
}
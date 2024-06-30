#include "Chunk.h"

Chunk::Chunk(glm::vec3 pos, glm::vec3 size)
	:m_pos(pos), m_size(size), m_texture("res/textures/tex.png"), m_shader("res/shaders/obj.frag", "res/shaders/obj.vert")
{
	for (int x = 0; x < m_size.x; x++)
	{
		for (int y = 0; y < m_size.y; y++)
		{
			for (int z = 0; z < m_size.z; z++)
			{
				Cube cube(m_shader, m_texture);
				m_cubes.emplace(glm::vec3(x, y, z), cube);
			}
		}
	}

	std::cout << "Number of cubes in chunk: " << m_cubes.size() << std::endl;

	for (auto& cube : m_cubes)
	{
		if (m_cubes.find(glm::vec3(cube.first.x, cube.first.y, cube.first.z + 1)) == m_cubes.end())
		{
			cube.second.AddFace(BlockFaceType::FRONT);
		}

		if (m_cubes.find(glm::vec3(cube.first.x, cube.first.y, cube.first.z - 1)) == m_cubes.end())
		{
			cube.second.AddFace(BlockFaceType::BACK);
		}

		if (m_cubes.find(glm::vec3(cube.first.x - 1, cube.first.y, cube.first.z)) == m_cubes.end())
		{
			cube.second.AddFace(BlockFaceType::LEFT);
		}

		if (m_cubes.find(glm::vec3(cube.first.x + 1, cube.first.y, cube.first.z)) == m_cubes.end())
		{
			cube.second.AddFace(BlockFaceType::RIGHT);
		}

		if (m_cubes.find(glm::vec3(cube.first.x, cube.first.y - 1, cube.first.z)) == m_cubes.end())
		{
			cube.second.AddFace(BlockFaceType::BOTTOM);
		}

		if (m_cubes.find(glm::vec3(cube.first.x, cube.first.y + 1, cube.first.z)) == m_cubes.end())
		{
			cube.second.AddFace(BlockFaceType::TOP);
		}

		std::cout << "Adding faces for cube at position (" << cube.first.x << ", " << cube.first.y << ", " << cube.first.z << ")" << std::endl;
	}
}

void Chunk::Draw(glm::mat4 proj, glm::mat4 view, glm::vec3 camPos)
{
	for (auto& cube : m_cubes)
	{
		std::cout << cube.second.m_vertexData.size() << std::endl;
		if (cube.second.m_vertexData.size() <= 1) return;
		cube.second.CreateVertexBuffer();
		std::cout << "Drawing Cube!" << std::endl;
		cube.second.Draw(proj, view, camPos, cube.first);
	}
}
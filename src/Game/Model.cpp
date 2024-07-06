#include "Model.h"

std::vector<std::string> split(std::string line, std::string delimeter)
{
	std::vector<std::string> splitLine;

	size_t pos = 0;
	std::string token;
	while ((pos = line.find(delimeter)) != std::string::npos)
	{
		token = line.substr(0, pos);
		splitLine.push_back(token);
		line.erase(0, pos + delimeter.size());
	}
	splitLine.push_back(line);

	return splitLine;
}

glm::vec2 read_vec2(std::vector<std::string> words)
{
	return glm::vec2(std::stof(words[1]), std::stof(words[2]));
}

glm::vec3 read_vec3(std::vector<std::string> words)
{
	return glm::vec3(std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));
}

void read_corner(std::string description, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt,
	std::vector<glm::vec3>& vn, std::vector<float>& vertices)
{
	std::vector<std::string> v_vt_vn = split(description, "/");

	// positions
	glm::vec3 pos = v[std::stol(v_vt_vn[0]) - 1];
	vertices.push_back(pos[0]);
	vertices.push_back(pos[1]);
	vertices.push_back(pos[2]);

	// tex coordinates
	glm::vec2 tex = vt[std::stol(v_vt_vn[1]) - 1];
	vertices.push_back(tex[0]);
	vertices.push_back(tex[1]);

	// normals
	glm::vec3 normal = vn[std::stol(v_vt_vn[2]) - 1];
	vertices.push_back(normal[0]);
	vertices.push_back(normal[1]);
	vertices.push_back(normal[2]);
}

void read_face(std::vector<std::string> words, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt,
	std::vector<glm::vec3>& vn, std::vector<float>& vertices)
{
	size_t triangleCount = words.size() - 3;

	for (size_t i = 0; i < triangleCount; ++i)
	{
		read_corner(words[1], v, vt, vn, vertices);
		read_corner(words[2 + i], v, vt, vn, vertices);
		read_corner(words[3 + i], v, vt, vn, vertices);
	}
}

Model::Model(const char* path, Shader shader, Texture texture)
	:m_Shader(shader), m_Texture(texture)
{
	size_t vertexCount = 0;
	size_t normalCount = 0;
	size_t texCoordCount = 0;

	std::string line;
	std::vector<std::string> words;

	std::ifstream file;
	file.open(path);

	if (!file)
	{
		std::cerr << "Error while loading the model file!" << std::endl;
	}

	while (std::getline(file, line))
	{
		words = split(line, " ");

		if (!words[0].compare("v"))
		{
			v.push_back(read_vec3(words));
		}
		else if (!words[0].compare("vn"))
		{
			vn.push_back(read_vec3(words));
		}
		else if (!words[0].compare("vt"))
		{
			vt.push_back(read_vec2(words));
		}
		else if (!words[0].compare("f"))
		{
			read_face(words, v, vt, vn, vertices);
		}
	}

	file.close();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	VertexBuffer* vb = new VertexBuffer(&vertices, sizeof(vertices));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(2);
}

void Model::Draw(glm::mat4 proj, glm::mat4 view, glm::vec3 camPos, glm::vec3 pos, float rotation, glm::vec3 scale)
{
	glm::mat4 model = glm::mat4(1.f);
	model = glm::translate(model, pos);
	model = glm::rotate(model, glm::radians(rotation), glm::vec3(1.0f, 0.5f, 0.5f));

	m_Texture.Bind();
	m_Shader.Bind();
	m_Shader.setMat4("proj", proj);
	m_Shader.setMat4("view", view);
	m_Shader.setMat4("model", model);
	m_Shader.setVec3("viewPos", camPos);
	m_Shader.setI("ourTexture", 0);

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0); // Unbinding it
}

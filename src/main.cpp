#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

#include "Game/Camera.h"

#include <GLFW/glfw3.h>

#include <iostream>

Camera cam;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	cam.mouse_callback(window, xpos, ypos);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Hello World", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Error while creating window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	float vertices[] = {
		// Front face
		// Position            // Color         // UV
		-0.5, -0.5,  0.5,       1.0, 0.0, 0.0,  0.0, 0.0,       // Bottom left
		 0.5, -0.5,  0.5,       0.0, 1.0, 0.0,  1.0, 0.0,       // Bottom right
		 0.5,  0.5,  0.5,       0.0, 0.0, 1.0,  1.0, 1.0,       // Top right
		-0.5,  0.5,  0.5,       1.0, 1.0, 0.0,  0.0, 1.0,       // Top left

		// Back face
		-0.5, -0.5, -0.5,       1.0, 0.0, 0.0,  1.0, 0.0,       // Bottom left
		 0.5, -0.5, -0.5,       0.0, 1.0, 0.0,  0.0, 0.0,       // Bottom right
		 0.5,  0.5, -0.5,       0.0, 0.0, 1.0,  0.0, 1.0,       // Top right
		-0.5,  0.5, -0.5,       1.0, 1.0, 0.0,  1.0, 1.0        // Top left
	};

	unsigned int indices[] = {
		// Front face
		0, 1, 2,
		2, 3, 0,

		// Right face
		1, 5, 6,
		6, 2, 1,

		// Back face
		7, 6, 5,
		5, 4, 7,

		// Left face
		4, 0, 3,
		3, 7, 4,

		// Bottom face
		4, 5, 1,
		1, 0, 4,

		// Top face
		3, 2, 6,
		6, 7, 3
	};

	{ // -> scope to delete the stack allocated objects before "glTerminate
		unsigned int VAO;

		IndexBuffer IBO(indices, sizeof(indices));

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		VertexBuffer VBO(vertices, sizeof(vertices));
		
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(0 * sizeof(float)));
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Shaders

		Texture texture("res/textures/tex.png");
		Shader triShader("./res/shaders/frag.shader", "./res/shaders/vert.shader");
		
		// Shaders End

		triShader.setMat4("proj", cam.getProjMatrix());

		glm::vec3 cubePositions[] = {
			glm::vec3(0.0f,  0.0f,  0.0f),
			glm::vec3(2.0f,  5.0f, -15.0f),
			glm::vec3(-1.5f, -2.2f, -2.5f),
			glm::vec3(-3.8f, -2.0f, -12.3f),
			glm::vec3(2.4f, -0.4f, -3.5f),
			glm::vec3(-1.7f,  3.0f, -7.5f),
			glm::vec3(1.3f, -2.0f, -2.5f),
			glm::vec3(1.5f,  2.0f, -2.5f),
			glm::vec3(1.5f,  0.2f, -1.5f),
			glm::vec3(-1.3f,  1.0f, -1.5f)
		};

		glEnable(GL_DEPTH_TEST);
		glfwSetCursorPosCallback(window, mouse_callback);

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.05f, 0.15f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// Rendering

			texture.Bind();
			triShader.setI("ourTexture", 0);

			glBindVertexArray(VAO);
			IBO.Bind();

			cam.update(window);
			triShader.setMat4("view", cam.getViewMatrix());

			for (const glm::vec3 &cubePos : cubePositions)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::mat4(1.f);
				model = glm::translate(model, cubePos);

				float rot = cubePos.x == 0 ? 20.f : cubePos.x * 20.f;
				float scale = sin(glfwGetTime()) * 1.f;

				model = glm::rotate(model, ((float)glfwGetTime()) * glm::radians(rot), glm::vec3(1.f, .3f, .5f));
				model = glm::scale(model, glm::abs(glm::vec3(scale)));
				triShader.setMat4("model", model);

				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);// 2 -> no. of indicies
			}

			// Ends

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}
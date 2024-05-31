#include "OpenGL/Shader.h"
#include "OpenGL/Texture.h"
#include "OpenGL/VertexBuffer.h"
#include "OpenGL/IndexBuffer.h"

#include <GLFW/glfw3.h>

#include <iostream>


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
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	{ // -> scope to delete the stack allocated objects before "glTerminate"
		IndexBuffer IBO(indices, sizeof(indices));

		unsigned int VAO;

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

		while (!glfwWindowShouldClose(window))
		{
			glClearColor(0.05f, 0.15f, 0.15f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Rendering

			texture.Bind();
			triShader.setI("ourTexture", 0);

			glBindVertexArray(VAO);
			IBO.Bind();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);// 2 -> no. of indicies

			// Ends

			glfwSwapBuffers(window);
			glfwPollEvents();
		}

	}

	glfwTerminate();
	return 0;
}
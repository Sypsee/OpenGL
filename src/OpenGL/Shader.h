#ifndef SHADER_H
#endif
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	Shader(const char* fragPath, const char* vertPath);
	void Bind() const;

	void setF4(const std::string u_name, float v1, float v2, float v3, float v4);
	void setF(const std::string u_name, float v1);
	void setI(const std::string u_name, float v1);

private:
	unsigned int shaderId;
};
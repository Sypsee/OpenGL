#include "Shader.h"

Shader::Shader(const char* fragPath, const char* vertPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertPath);
        fShaderFile.open(fragPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();


    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShaderCode, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
    glCompileShader(fragmentShader);

    shaderId = glCreateProgram();
    glAttachShader(shaderId, vertexShader);
    glAttachShader(shaderId, fragmentShader);
    glLinkProgram(shaderId);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Bind() const
{
    glLinkProgram(shaderId);
    glUseProgram(shaderId);
}

void Shader::setF4(const std::string u_name, float v1, float v2, float v3, float v4)
{
	unsigned int loc = glGetUniformLocation(shaderId, u_name.c_str());
	glUseProgram(shaderId);
	glUniform4f(loc, v1, v2, v3, v4);
}

void Shader::setF(const std::string u_name, float v1)
{
    unsigned int loc = glGetUniformLocation(shaderId, u_name.c_str());
    glUseProgram(shaderId);
    glUniform1f(loc, v1);
}

void Shader::setI(const std::string u_name, float v1)
{
    unsigned int loc = glGetUniformLocation(shaderId, u_name.c_str());
    glUseProgram(shaderId);
    glUniform1i(loc, v1);
}

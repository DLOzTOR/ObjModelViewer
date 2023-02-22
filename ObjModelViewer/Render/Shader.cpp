#include "Shader.h"

bool Render::Shader::addVertexShader(std::string path)
{
	std::string shaderSource;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShader == 0) {
		return false;
	}
	ReadFile::ReadFromPathInOneString(path, shaderSource);
	const GLchar* codeArray[] = { shaderSource.c_str() };
	glShaderSource(vertexShader, 1, codeArray, nullptr);
	return true;
}

bool Render::Shader::addFragShader(std::string path)
{
	std::string shaderSource;
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragShader == 0) {
		return false;
	}
	ReadFile::ReadFromPathInOneString(path, shaderSource);
	const GLchar* codeArray[] = { shaderSource.c_str()};
	glShaderSource(fragShader, 1, codeArray, nullptr);
	return true;
}

bool Render::Shader::addAndCompileShader(std::string vert, std::string frag)
{
	if (!addVertexShader(vert)) {
		std::cout << "Create vertex shader problem!.\n";
		return false;
	}
	if (!addFragShader(frag)) {
		std::cout << "Create fragment shader problem!.\n";
		return false;
	}
	shaderHandle = glCreateProgram();
	if (0 == shaderHandle)
	{
		std::cout << "Error creating shader object.\n";
		return false;
	}
	glAttachShader(shaderHandle, vertexShader);
	glAttachShader(shaderHandle, fragShader);
	glLinkProgram(shaderHandle);
	glDeleteShader(vertexShader);
	glDeleteShader(fragShader);
	GLint status;
	glGetProgramiv(shaderHandle, GL_LINK_STATUS, &status);
	if (GL_FALSE == status) {
		std::cout << "Failed to link shader program!\n";
		GLint logLen;
		glGetProgramiv(shaderHandle, GL_INFO_LOG_LENGTH,
			&logLen);
		if (logLen > 0)
		{
			char* log = new char[logLen];
			GLsizei written;
			glGetProgramInfoLog(shaderHandle, logLen, &written, log);
			std::cout << "Program log: \n" << log << std::endl;
			delete[] log;
		}
		return false;
	}
	isShaderCompiled = true;
	return true;
}
#pragma once
#include "glewInit.h"
#include <iostream>
#include "../Utils/ReadFile.h"
namespace Render{
	class Shader
	{
	private:
		bool addVertexShader(std::string path);
		bool addFragShader(std::string path);
		GLuint vertexShader;
		GLuint fragShader;
		bool isShaderCompiled;

	public:
		GLuint shaderHandle;
		~Shader() {
			glDeleteProgram(shaderHandle);
		}
		bool addAndCompileShader(std::string vert, std::string frag);
		void Use() {
			if (isShaderCompiled) {
				glUseProgram(shaderHandle);
			}
			else
				std::cout << "shader isn't compiled.\n";
		}
	};
}


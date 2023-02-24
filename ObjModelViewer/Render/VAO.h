#pragma once
#include "glewInit.h"
#include <vector>
#include <string>
#include "..\Utils\ReadFile.h"
#include "..\Utils\StringParce.h"
namespace Render {
	class VAO
	{
	private:
		GLuint vaoId;
		GLuint VAOposId;
		GLuint UIposId;
	public:
		GLuint flatCount;
		VAO();
		~VAO();
		void Bind() {
			glBindVertexArray(vaoId);
		}
		void addVBO(const std::vector<float>& data);
		void Draw();
		void LoadFromObj(std::string path);
	};
}


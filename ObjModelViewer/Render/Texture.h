#pragma once
#include <SFML/Graphics.hpp>
#include "glewInit.h"
#include <string>
namespace Render {
	class Texture
	{
	private:
		GLuint textureId;
	public:
		~Texture();
		void LoadTexture(std::string path);
		void Bind() {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureId);
		}
	};
}
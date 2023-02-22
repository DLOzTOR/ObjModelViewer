#include "Texture.h"

Render::Texture::~Texture()
{
	glDeleteTextures(1, &textureId);
}

void Render::Texture::LoadTexture(std::string path) {
	sf::Image texture;
	texture.loadFromFile(path);
	texture.flipHorizontally();
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture.getSize().x, texture.getSize().y, 0, GL_RGB, GL_UNSIGNED_BYTE, texture.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);
}

#pragma once
#include "../Utils/ReadFile.h"
#include "../Utils/StringParce.h"
#include "VAO.h"
#include "Texture.h"
#include <iostream>
namespace Render {
	class Model
	{
	public:
		Render::VAO vao;
		Render::Texture texture;
		void LoadFromObj(std::string path);
		void Draw() {
			vao.Bind();
			texture.Bind();
			vao.Draw();
		}
	};
}
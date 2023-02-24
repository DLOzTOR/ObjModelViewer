#pragma once
#include "../Render/Model.h"
#include <glm/glm.hpp>
namespace Engine {
	class Entity
	{
	public:
		Render::Model model;
		glm::mat4 transform = glm::mat4(1.f);
	};
}


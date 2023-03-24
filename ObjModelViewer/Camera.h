#pragma once
#include <glm/glm.hpp>
namespace Engine {
	class Camera
	{
	private:
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	public:
		glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
		glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
		glm::vec3 cameraDirection;
		glm::vec3 GetCameraDirection() {
			return cameraDirection = glm::normalize(cameraPos - cameraTarget);
		}
	};
}


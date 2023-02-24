#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <cstdlib>
#include <cmath>


#define xSize 65
#define ySize 65


namespace Engine {
	class Terrain : Entity
	{
	public:
		GLuint vaoId;
		GLuint vboId;
		std::vector<GLfloat> verticles;
		GLuint veticlesCount;
		void GenerateTerraine();
		void Draw();
		~Terrain() {
			glDeleteBuffers(1,&vboId);
			glDeleteVertexArrays(1, &vaoId);
		}
	};
	struct Quad {
		glm::vec3 vertices[4];
		glm::vec3* triangulate(){
			glm::vec3 t[] = { vertices[0],vertices[1],vertices[3],
						      vertices[1],vertices[2],vertices[3]};
			return t;
		}
	};
}


#pragma once
#include "Entity.h"
#include <glm/glm.hpp>
#include <vector>
#include <random>
#include <cstdlib>
#include <cmath>


#define xSize 50
#define ySize 50


namespace Engine {
	class Terrain : Entity
	{
	public:
		//GLuint modeOfRender = GL_LINES;
		GLuint modeOfRender = GL_TRIANGLES;
		GLuint vaoId;
		GLuint vboId;
		GLuint veticlesCount;
		void GenerateTerraine();
		void Draw();
		~Terrain() {
			glDeleteBuffers(1,&vboId);
			glDeleteVertexArrays(1, &vaoId);
		}
	};
	class Quad {
	public:
		glm::vec3* vertices = new glm::vec3[4];
		glm::vec3* triangulate(){
			glm::vec3 t[] = { vertices[0],vertices[1],vertices[3],
						      vertices[1],vertices[2],vertices[3]};
			return t;
		}
		glm::vec3* GetLines() {
			glm::vec3 t[] = { vertices[0],vertices[1],
				vertices[1],vertices[2],
				vertices[2],vertices[3],
				vertices[3],vertices[0],
				vertices[1],vertices[3]
			};
			return t;
		}
		~Quad(){
			delete[] vertices;
		}
	};
}


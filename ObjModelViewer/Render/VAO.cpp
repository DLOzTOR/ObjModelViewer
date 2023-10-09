#include "VAO.h"
#include <glm/glm.hpp>
#include <iostream>
Render::VAO::VAO()
{
	glGenVertexArrays(1, &vaoId);
}

Render::VAO::~VAO()
{
	glDeleteBuffers(1, &VAOposId);
	glDeleteBuffers(1, &UIposId);
	glDeleteVertexArrays(1, &vaoId);
}

void Render::VAO::Draw()
{
	Bind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glDrawArrays(GL_TRIANGLES, 0, flatCount);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}
void Render::VAO::LoadFromObj(std::string path)
{
	std::vector<std::string> fileLines = ReadFile::ReadFromPath(path);
	std::vector<glm::vec3> vertices;
	std::vector<GLfloat> verticesInd;
	std::vector<glm::vec2> uvcords;
	std::vector<float> uvcordsInd;
	std::vector<GLuint> idicies;
	std::vector<GLuint> uvIdicies;
	for (int i = 0; i < fileLines.size(); i++)
	{
		std::vector<std::string> splitedString = StringParce::Split(fileLines[i], " ");
		if (std::strcmp(splitedString[0].c_str(), "v") == 0) {
			glm::vec3 vertex;
			vertex.x = std::stof(splitedString[1]); 
			vertex.y = std::stof(splitedString[2]); 
			vertex.z = std::stof(splitedString[3]);
			vertices.push_back(vertex);
		}
		else if (std::strcmp(splitedString[0].c_str(), "vt") == 0) {
			glm::vec2 uvCord;
			uvCord.x = std::stof(splitedString[1]);
			uvCord.y = std::stof(splitedString[2]);
			uvcords.push_back(uvCord);
		}
		else if (std::strcmp(splitedString[0].c_str(), "f") == 0) {
			idicies.push_back(std::stoi(StringParce::Split(splitedString[1], "/")[0]) - 1);
			idicies.push_back(std::stoi(StringParce::Split(splitedString[2], "/")[0]) - 1);
			idicies.push_back(std::stoi(StringParce::Split(splitedString[3], "/")[0]) - 1);
			uvIdicies.push_back(std::stoi(StringParce::Split(splitedString[1], "/")[1]) - 1);
			uvIdicies.push_back(std::stoi(StringParce::Split(splitedString[2], "/")[1]) - 1);
			uvIdicies.push_back(std::stoi(StringParce::Split(splitedString[3], "/")[1]) - 1);
		}
	}

	std::cout << idicies.size() <<std::endl;
	for (unsigned int i = 0; i < idicies.size(); i++) {
		verticesInd.push_back(vertices[(idicies[i])].x);
		verticesInd.push_back(vertices[(idicies[i])].z);
		verticesInd.push_back(vertices[(idicies[i])].y);
	}	
	std::cout << verticesInd.size() << std::endl;
	for (unsigned int i = 0; i < uvIdicies.size(); i++) {
		uvcordsInd.push_back(uvcords[uvIdicies[i]].x);
		uvcordsInd.push_back(uvcords[uvIdicies[i]].y);
	}
	glBindVertexArray(vaoId);
	glGenBuffers(1, &VAOposId);
	glBindBuffer(GL_ARRAY_BUFFER, VAOposId);
	glBufferData(GL_ARRAY_BUFFER, verticesInd.size() * sizeof(GLfloat), verticesInd.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glGenBuffers(1, &UIposId);
	glBindBuffer(GL_ARRAY_BUFFER, UIposId);
	glEnableVertexAttribArray(1);
	glBufferData(GL_ARRAY_BUFFER, uvcordsInd.size() * sizeof(GLfloat), uvcordsInd.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	flatCount = verticesInd.size() / 3;
}
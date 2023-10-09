#include "Terrain.h"

void Engine::Terrain::GenerateTerraine()
{
	std::srand((unsigned)std::time(NULL));
	std::vector<GLfloat> verticles;
	GLfloat*** qt = new GLfloat** [xSize];
	for (int i = 0; i < xSize; i++) {
		qt[i] = new GLfloat* [ySize];
		for (int j = 0; j < ySize; j++) {
			qt[i][j] = new GLfloat[3];
		}
	}
	Quad** q = new Quad* [xSize - 1];
	for (int i = 0; i < xSize - 1; i++) {
		q[i] = new Quad[ySize - 1];
	}
	for (int i = 0; i < ySize; i++)
	{
		for (int j = 0; j < xSize; j++)
		{
			qt[j][i][0] = GLfloat (j - (xSize - 1) / 2);
			qt[j][i][1] = GLfloat(i - (ySize - 1) / 2);
			qt[j][i][2] = GLfloat(-static_cast<GLfloat>(std::rand()) / (RAND_MAX  /6));
		}
	}
	for (int i = 0; i < ySize - 1; i++)
	{
		for (int j = 0; j < xSize - 1; j++)
		{
			q[i][j].vertices[0] = glm::vec3(qt[j][i][0], qt[j][i][1], qt[j][i][2]);
			q[i][j].vertices[1] = glm::vec3(qt[j + 1][i][0], qt[j + 1][i][1], qt[j + 1][i][2]);
			q[i][j].vertices[2] = glm::vec3(qt[j + 1][i + 1][0], qt[j + 1][i + 1][1], qt[j + 1][i + 1][2]);
			q[i][j].vertices[3] = glm::vec3(qt[j][i + 1][0], qt[j][i + 1][1], qt[j][i + 1][2]);
		}		
	}
	for (int x = 0; x < xSize; x++) {
		for (int y = 0; y < ySize; y++) {
			delete [] qt[x][y];
		}
		delete[] qt[x];
	}
	delete[] qt;
	if(modeOfRender == GL_TRIANGLES)
	for (int i = 0; i < xSize - 1; i++)
	{
		for (int j = 0; j < ySize - 1; j++)
		{
			glm::vec3* vals = q[i][j].triangulate();
			for (int k = 0; k < 6; k++)
			{
				verticles.push_back(vals[k].x);
				verticles.push_back(vals[k].y);
				verticles.push_back(vals[k].z);
			}
		}
	}
	else if(modeOfRender == GL_LINES)
	for (int i = 0; i < ySize - 1; i++)
	{
		for (int j = 0; j < xSize - 1; j++)
		{
			glm::vec3* vals = q[i][j].GetLines();
			for (int k = 0; k < 10; k++)
			{
				verticles.push_back(vals[k].x);
				verticles.push_back(vals[k].y);
				verticles.push_back(vals[k].z);
			}
		}
	}
	for (int x = 0; x < xSize - 1; x++) {
		delete[] q[x];
	}
	delete[] q;
	veticlesCount = verticles.size();
	glBindVertexArray(vaoId);
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, verticles.size() * sizeof(GLfloat), verticles.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Engine::Terrain::Draw()
{
	glBindVertexArray(vaoId);
	glEnableVertexAttribArray(0);
	glDrawArrays(modeOfRender, 0, veticlesCount / 3);
	glDisableVertexAttribArray(0);
}
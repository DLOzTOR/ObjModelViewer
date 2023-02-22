#include "Model.h"

void Render::Model::LoadFromObj(std::string path)
{
	vao.LoadFromObj(path);
}

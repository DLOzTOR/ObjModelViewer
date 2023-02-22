#pragma once
#include<vector>
#include<string>
#include <fstream>
#include <string>

namespace ReadFile {
	std::vector<std::string> ReadFromPath(std::string path);
	void ReadFromPathInOneString(std::string path, std::string &outstr);
}
#include "ReadFile.h"

std::vector<std::string> ReadFile::ReadFromPath(std::string path)
{
    std::vector<std::string> fileLines;
    std::ifstream file(path.c_str());
    std::string str;
    while (std::getline(file, str))
    {
        fileLines.push_back(str);
    }
    return fileLines;
}

void ReadFile::ReadFromPathInOneString(std::string path, std::string &outstr)
{
    std::ifstream file(path.c_str());
    std::string str;
    while (std::getline(file, str))
    {
        outstr += str + "\n";
    }
}

#include "StringParce.h"

std::vector<std::string> StringParce::Split(std::string str, std::string splitBy)
{
    std::vector<std::string> splitedString;
    size_t index;
    while ((index = str.find(splitBy)) != std::string::npos) {
        splitedString.push_back(str.substr(0, index));
        str.erase(0, index + splitBy.length());
    }
    splitedString.push_back(str);
    return splitedString;
}

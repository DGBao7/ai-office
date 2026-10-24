#include "utils/Json.h"

namespace utils
{
    Json::Json(std::string path)
    {
        std::ifstream file(path);

        file >> this -> data;
    }

    std::vector<std::string> Json::_get(std::string key)
    {
        return this -> data[key]["models"];
    }
}
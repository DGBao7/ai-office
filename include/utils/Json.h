#ifndef JSON_H
#define JSON_H

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>

using json = nlohmann::json;

namespace utils
{
    class Json
    {
    private:
        json data;    

    public:
        Json(std::string path);

        std::vector<std::string> _get(std::string key);
    };
}

#endif
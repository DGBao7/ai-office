#ifndef ENV_H
#define ENV_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <vector>
#include <iostream>

namespace utils
{
    class Env
    {
    private:
        std::unordered_map<std::string , std::string> env;

    public:
        bool _load(const std::string path = ".env");
        std::string _get(const std::string key);

        std::unordered_map<std::string , std::string> _get_APIs();
    };

    Env *_run_env();
}

#endif
#include "utils/Env.h"

#ifndef ENV_FILE_PATH
#define ENV_FILE_PATH ".env"
#endif

namespace utils
{
    bool Env::_load(const std::string path)
    {
        std::ifstream file (
            path == ".env" ? ENV_FILE_PATH : path
        );

        if (!file.is_open())
        {
            return false;
        }

        std::string line;

        while (std::getline(file , line))
        {
            if (line.empty() || line[0] == '#')
            {
                continue;
            }

            std::size_t confirm = line.find('=');

            if (confirm == std::string::npos)
            {
                continue;
            }

            std::string key = line.substr(0 , confirm);
            std::string value = line.substr(confirm + 1);

            if (!key.empty())
            {
                this -> env[key] = value;
            }
        }

        return true;
    }

    std::string Env::_get(const std::string key)
    {
        auto it = this -> env.find(key);

        if (it == env.end())
        {
            return "";
        }

        return it -> second;
    }

    std::unordered_map<std::string , std::string> Env::_get_APIs()
    {
        return this -> env;
    }

    Env *_run_env()
    {
        Env *env = new Env();

        if (!env -> _load())
        {
std::cout << "Cannot load .env\n";

            delete env;

            return nullptr;
        }

        return env;
    }
}
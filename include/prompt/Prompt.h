#ifndef PROMPT_H
#define PROMPT_H

#include <string>
#include <nlohmann/json.hpp>

namespace prompt
{
    class Prompt
    {
    protected:
        std::string input;
        std::string prompt;

    public:
        Prompt();

        void _get_user_input(std::string input);

        nlohmann::json _return_prompt(std::string role);
    };
}

#endif
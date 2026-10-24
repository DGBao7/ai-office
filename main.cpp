#include "utils/Env.h"
#include "utils/Json.h"

#include "providers/GroqProvider.h"
#include "providers/OpenRouterProvider.h"
#include "providers/Provider.h"
#include "providers/Initializer.h"

#include "HR/Hr.h"

#include "prompt/Prompt.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include <memory>

// env
utils::Env *_run_env()
{
    utils::Env *env = utils::_run_env();

    return env;
}

std::vector<std::unique_ptr<providers::Provider>> _recruit()
{
    utils::Env *env = _run_env();

    utils::Json *models = new utils::Json("../configs/models.json");

    providers::Init init;
    init._init(*env , "groq" , *models);
    init._init(*env , "openrouter" , *models);

    std::vector<std::unique_ptr<providers::Provider>> &agents =
        init._return_models();

    return std::move(agents);
}

int main()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    std::vector<std::unique_ptr<providers::Provider>> agents =
        _recruit();

    hr::SoftwareEngineer *software_engineer = new hr::SoftwareEngineer(
        "software engineer" ,
        agents
    );

    hr::SoftwareArchitect *software_architect = new hr::SoftwareArchitect(
        "software architect" ,
        agents
    );

    hr::QaEngineer *qa_engineer = new hr::QaEngineer(
        "qa engineer" ,
        agents
    );

    prompt::Prompt *prompt = new prompt::Prompt();

    while (true)
    {
        std::string input;
        std::cout << "Enter: ";
        std::getline(std::cin , input);

        if (input == "")
        {
            break;
        }

        prompt -> _get_user_input(input);
        nlohmann::json architect = prompt -> _return_prompt("software architect");
    }

    std::string one;
    std::getline(std::cin , one);
}
#include "utils/Env.h"
#include "utils/Json.h"

#include "providers/GroqProvider.h"
#include "providers/OpenRouterProvider.h"
#include "providers/Provider.h"
#include "providers/Initializer.h"

#include "HR/Hr.h"
#include "HR/SoftwareArchitect.h"
#include "HR/SoftwareEngineer.h"
#include "HR/QaEngineer.h"

#include "prompt/Prompt.h"

#include "server/HttpServer.h"

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

    server::_start();

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

        nlohmann::json agent_prompt = prompt -> _return_prompt("software architect");
        std::string architect_response = software_architect -> _run(agent_prompt , input);

        agent_prompt = prompt -> _return_prompt("software engineer");
        std::string engineer_response = software_engineer -> _run(agent_prompt , architect_response);

        agent_prompt = prompt -> _return_prompt("qa engineer");
        std::string qa_response = qa_engineer -> _run(agent_prompt , engineer_response);

        std::cout << qa_response << "\n";

        std::cout << "\n";
    }

    std::string one;
    std::getline(std::cin , one);
}
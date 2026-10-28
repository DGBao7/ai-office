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

#include "contact/Memory.h"

#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include <memory>
#include <mutex>

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

    hr::SoftwareEngineer *software_engineer =
        new hr::SoftwareEngineer(
            "software engineer" ,
            agents
        );

    hr::SoftwareArchitect *software_architect =
        new hr::SoftwareArchitect(
            "software architect" ,
            agents
        );

    hr::QaEngineer *qa_engineer =
        new hr::QaEngineer(
            "qa engineer" ,
            agents
        );

    prompt::Prompt *prompt = new prompt::Prompt();

    contact::Memory *memory = new contact::Memory();

    std::mutex chat_mutex;

    server::ChatHandler chat_handler = [&] (const std::string &input) -> std::string
    {
        std::lock_guard<std::mutex> lock(chat_mutex);

        memory -> _save_contact(input , "user");

        prompt -> _get_user_input(input);

        std::vector<std::string> memory_flow = memory -> _return_flow();

        nlohmann::json agent_prompt = prompt -> _return_prompt("software architect");

        std::string architect_response =
            software_architect -> _run(
                agent_prompt ,
                input ,
                memory_flow
            );

        agent_prompt = prompt -> _return_prompt("software engineer");

        std::string engineer_response =
            software_engineer -> _run(
                agent_prompt ,
                architect_response ,
                memory_flow
            );

        agent_prompt = prompt -> _return_prompt("qa engineer");

        std::string qa_response =
            qa_engineer -> _run(
                agent_prompt ,
                engineer_response ,
                memory_flow
            );

        memory -> _save_contact(qa_response , "assistant");

        return qa_response;
    };

    server::_start(chat_handler);

    delete memory;
    delete prompt;
    delete qa_engineer;
    delete software_architect;
    delete software_engineer;
}
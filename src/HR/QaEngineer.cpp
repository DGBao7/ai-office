#include "HR/QaEngineer.h"

namespace hr
{
    QaEngineer::QaEngineer(
        std::string name ,
        std::vector<std::unique_ptr<providers::Provider>> &agents
    )
        : Divisions(name , agents)
    {
        this -> manager = this -> agents[1].get();
        this -> employee = this -> agents[2].get();
    }

    std::string QaEngineer::_backup(
        nlohmann::json prompt ,
        std::string input
    )
    {
        nlohmann::json request = prompt;
        request["user_request"] = input;

        std::string question = request.dump();

        std::string output = this -> employee -> _ask(question);

        return output;
    }

    std::string QaEngineer::_run(
        nlohmann::json prompt ,
        std::string input
    )
    {
        std::string manager_error;

        nlohmann::json request = prompt;
        request["user_request"] = input;

        if (prompt.empty())
        {
            return "hr/architect prompt blank\n";
        }

        std::string question = request.dump();

        try
        {
            std::string output = this -> manager -> _ask(question);

            bool api_error = output.find(" API error:") != std::string::npos;

            if (!utils::_is_blank(output) && !api_error)

            if (!utils::_is_blank(output))
            {
                return output;
            }
        }
        catch (std::exception &error)
        {
            manager_error = "hr/architect " + std::string(error.what());
        }
        catch (...)
        {
            manager_error = "hr/architect manager error\n";
        }

std::cout << "hr/architect manager error\n";
std::cout << manager_error << "\n";
std::cout << "switch to employee\n";

        return this -> _backup(prompt , input);
    }
}
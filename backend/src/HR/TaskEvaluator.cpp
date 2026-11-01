#include "HR/TaskEvaluator.h"

namespace hr
{
    TaskEvaluator::TaskEvaluator(
        std::string name ,
        std::vector<std::unique_ptr<providers::Provider>> &agents
    )
        : Divisions(name , agents)
    {
        this -> manager = this -> agents[0].get();
        this -> employee = this -> agents[2].get();
    }

    std::string TaskEvaluator::_backup(
        nlohmann::json prompt ,
        std::string input ,
        std::vector<std::string> &memory
    )
    {
        nlohmann::json request = prompt;
        request["user_request"] = input;

        std::string question = request.dump();

        std::string output = this -> employee -> _ask(question);

        return output;
    }

    std::string TaskEvaluator::_run(
        nlohmann::json prompt ,
        std::string input ,
        std::vector<std::string> &memory
    )
    {
        std::string manager_error;

        nlohmann::json request = prompt;
        request["user_request"] = input;
        request["memory"] = memory;

        if (prompt.empty())
        {
            return "hr/task evaluator prompt blank\n";
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
            manager_error = "hr/task evaluator " + std::string(error.what());
        }
        catch (...)
        {
            manager_error = "hr/task evaluator manager error\n";
        }

std::cout << "hr/task evaluator manager error\n";
std::cout << manager_error << "\n";
std::cout << "switch to employee\n";

        return this -> _backup(prompt , input , memory);
    }
}
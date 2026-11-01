#ifndef TASKEVALUATOR_H
#define TASKEVALUATOR_H

#include "HR/Hr.h"

#include "utils/Str.h"

#include <string>
#include <memory>
#include <vector>
#include <nlohmann/json.hpp>
#include <exception>
#include <stdexcept>
#include <iostream>

namespace hr
{
    class TaskEvaluator : public Divisions
    {
    public:
        TaskEvaluator(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );  

        std::string _run(
            nlohmann::json prompt ,
            std::string input ,
            std::vector<std::string> &memory
        ) override;

        std::string _backup(
            nlohmann::json prompt ,
            std::string input ,
            std::vector<std::string> &memory
        ) override;
    };
}

#endif
#ifndef SOFTWAREENGINEER_H
#define SOFTWAREENGINEER_H

#include "providers/GroqProvider.h"

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
    class SoftwareEngineer : public Divisions
    {
    public:
        SoftwareEngineer(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );

        std::string _run(
            nlohmann::json prompt ,
            std::string input
        ) override;

        std::string _backup(
            nlohmann::json prompt ,
            std::string input
        ) override;
    };
}

#endif
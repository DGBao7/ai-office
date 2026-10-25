#ifndef HR_H
#define HR_H

#include "providers/Provider.h"
#include "providers/GroqProvider.h"
#include "providers/OpenRouterProvider.h"

#include <vector>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

namespace hr
{
    class Divisions
    {
    protected:
        std::string name;
        std::vector<std::unique_ptr<providers::Provider>> &agents;

        providers::Provider *manager = nullptr;
        providers::Provider *employee = nullptr;

    public:
        Divisions(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );

        virtual std::string _run(
            nlohmann::json prompt ,
            std::string input
        );

        virtual std::string _backup(
            nlohmann::json prompt ,
            std::string input
        );
    };
}

#endif
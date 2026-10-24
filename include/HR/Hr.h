#ifndef HR_H
#define HR_H

#include "providers/Provider.h"
#include "providers/GroqProvider.h"
#include "providers/OpenRouterProvider.h"

#include <vector>
#include <memory>
#include <string>

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
    };

    class SoftwareEngineer : public Divisions
    {
    public:
        SoftwareEngineer(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );
    };

    class SoftwareArchitect : public Divisions
    {
    public:
        SoftwareArchitect(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );
    };

    class QaEngineer : public Divisions
    {
    public: 
        QaEngineer(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );
    };
}

#endif
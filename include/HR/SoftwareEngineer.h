#ifndef SOFTWAREENGINEER_H
#define SOFTWAREENGINEER_H

#include "providers/GroqProvider.h"

#include "HR/Hr.h"

#include <string>
#include <memory>
#include <vector>

namespace hr
{
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
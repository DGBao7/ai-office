#include "HR/Hr.h"

namespace hr
{
    Divisions::Divisions(
        std::string name ,
        std::vector<std::unique_ptr<providers::Provider>> &agents
    )
        : name(name) ,
        agents(agents)
    {}

    SoftwareEngineer::SoftwareEngineer(
        std::string name ,
        std::vector<std::unique_ptr<providers::Provider>> &agents
    )
        : Divisions(name , agents)
    {
        this -> manager = this -> agents[1].get();
        this -> manager = this -> agents[0].get();
    }

    QaEngineer::QaEngineer(
        std::string name ,
        std::vector<std::unique_ptr<providers::Provider>> &agents
    )
        : Divisions(name , agents)
    {
        this -> manager = this -> agents[1].get();
        this -> employee = this -> agents[2].get();
    }
}
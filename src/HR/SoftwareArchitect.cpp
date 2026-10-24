#include "HR/SoftwareArchitect.h"

namespace hr
{
    SoftwareArchitect::SoftwareArchitect(
        std::string name ,
        std::vector<std::unique_ptr<providers::Provider>> &agents
    )
        : Divisions(name , agents)
    {
        this -> manager = this -> agents[0].get();
        this -> employee = this -> agents[1].get();
    }
}
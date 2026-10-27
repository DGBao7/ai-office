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

    std::string Divisions::_run( 
        nlohmann::json prompt ,
        std::string input ,
        std::vector<std::string> &memory
    )
    {
        return "";
    }

    std::string Divisions::_backup(
        nlohmann::json prompt ,
        std::string input ,
        std::vector<std::string> &memory
    )
    {
        return "";
    }
}
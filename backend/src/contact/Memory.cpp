#include "contact/Memory.h"

namespace contact
{
    std::vector<std::string> Memory::_return_flow()
    {
        return this -> flow;
    }

    void Memory::_save_contact(std::string sentence , std::string role)
    {
        if (role == "user")
        {
            this -> flow.push_back(
                "user: " + sentence
            );
        }
        else if (role == "agents")
        {
            this -> flow.push_back(
                "agents: " + sentence
            );
        }
    }
}
#ifndef MEMORY_H
#define MEMORY_H

#include <string>
#include <vector>

namespace contact
{
    class Memory
    {
    private:
        std::vector<std::string> flow;

    public:
        std::vector<std::string> _return_flow();

        void _save_contact(std::string sentence , std::string role);
    };
}

#endif
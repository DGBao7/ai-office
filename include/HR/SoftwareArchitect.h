#ifndef SOFTWAREARCHITECT_H
#define SOFTWAREARCHITECT_H

#include "providers/Provider.h"

#include "HR/Hr.h"

namespace hr
{
    class SoftwareArchitect : public Divisions
    {
    public:
        SoftwareArchitect(
            std::string name ,
            std::vector<std::unique_ptr<providers::Provider>> &agents
        );
    };
}

#endif
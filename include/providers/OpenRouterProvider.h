#ifndef OPENROUTERPROVIDER_H
#define OPENROUTERPROVIDER_H

#include "utils/Env.h"
#include "providers/Provider.h"

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <exception>

namespace providers
{
    class OpenRouter : public Provider
    {
    public:
        OpenRouter(
            utils::Env &env ,
            std::string key ,
            std::string model
        );
        
        std::string _ask(nlohmann::json question) override;
    };
}

#endif
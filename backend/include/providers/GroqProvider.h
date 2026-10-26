#ifndef GROQPROVIDER_H
#define GROQPROVIDER_H

#include "utils/Env.h"
#include "providers/Provider.h"

#include <string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <exception>
#include <vector>

namespace providers
{
    class Groq : public Provider
    {
    public:
        Groq(
            utils::Env &env ,
            std::string key ,
            std::string model
        );

        std::string _ask(nlohmann::json question) override;
    };
}

#endif
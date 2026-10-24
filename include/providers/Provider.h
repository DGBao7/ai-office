#ifndef PROVIDER_H
#define PROVIDER_H

#include "utils/Env.h"

#include <string>
#include <nlohmann/json.hpp>

namespace providers
{
    class Provider
    {
    protected:
        std::string api_key;
        std::string model;

    public:
        Provider(
            utils::Env &env , 
            std::string key ,
            std::string model
        );

        std::string &_return_model();

        virtual std::string _ask(nlohmann::json question);
    };
}

#endif
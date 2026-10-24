#include "providers/Provider.h"

namespace providers
{
    Provider::Provider(
        utils::Env &env ,
        std::string key ,
        std::string model
    )
        : api_key(env._get(key)) ,
        model(model)
    {}

    std::string &Provider::_return_model()
    {
        return this -> model;
    }

    std::string Provider::_ask(nlohmann::json question)
    {
        return "abc";
    }
}
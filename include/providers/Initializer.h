#ifndef INITIALIZER_H
#define INITIALIZER_H

#include "providers/Provider.h"
#include "providers/GroqProvider.h"
#include "providers/OpenRouterProvider.h"

#include "utils/Json.h"
#include "utils/Env.h"

#include <memory>
#include <vector>
#include <string>

namespace providers
{
    class Init
    {
    protected:
        std::vector<std::unique_ptr<providers::Provider>> models;

    public:
        Init();

        void _init(
            utils::Env &env ,
            std::string key ,
            utils::Json &models
        );

        std::vector<std::unique_ptr<providers::Provider>> &_return_models();
    };
}

#endif
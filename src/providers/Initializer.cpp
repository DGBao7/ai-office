#include "providers/Initializer.h"

namespace providers
{
    Init::Init()
    {
    }

    void Init::_init(
        utils::Env &env ,
        std::string key ,
        utils::Json &models
    )
    {
        std::vector<std::string> models_key = models._get(key);

        for (auto model : models_key)
        {
            if (key == "groq")
            {
                this -> models.push_back(
                    std::make_unique<providers::Groq>(
                        env ,
                        "GROQ_API_KEY" ,
                        model
                    )
                );
            }
            else if (key == "openrouter")
            {
                this -> models.push_back(
                    std::make_unique<providers::OpenRouter>(
                        env ,
                        "OPENROUTER_API_KEY" ,
                        model
                    )
                );
            }
        }
    }

    std::vector<std::unique_ptr<providers::Provider>> &Init::_return_models()
    {
        return this -> models;
    }
}
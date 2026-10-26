#include "server/HttpServer.h"

namespace server
{
    using json = nlohmann::json;

    static bool _is_error(const std::string &result)
    {
        const std::vector<std::string> prefixes = {
            "Error:",
            "CURL error:",
            "Groq API error:",
            "Groq HTTP error:",
            "OpenRouter API error:",
            "OpenRouter HTTP error:",
            "Response parsing error:"
        };

        for (const auto &prefix : prefixes)
        {
            if (result.rfind(prefix , 0) == 0)
            {
                return true;
            }
        }

        return false;
    }

    void _start()
    {
        utils::Env env;

        if (!env._load())
        {
            std::cerr << "Cannot load .env\n";

            return;
        }

        utils::Json model_config(MODELS_FILE_PATH);

        std::vector<std::string> groq_models =
            model_config._get("groq");

        std::vector<std::string> openrouter_models =
            model_config._get("openrouter");

        providers::Init initializer;

        initializer._init(
            env ,
            "groq" ,
            model_config
        );

        initializer._init(
            env ,
            "openrouter" ,
            model_config
        );

        auto &models = initializer._return_models();

        const std::size_t openrouter_start = groq_models.size();

        const bool groq_available =
            !env._get("GROQ_API_KEY").empty() &&
            !groq_models.empty() &&
            models.size() >= groq_models.size();

        const bool openrouter_available =
            !env._get("OPENROUTER_API_KEY").empty() &&
            !openrouter_models.empty() &&
            models.size() >=
                groq_models.size() + openrouter_models.size();

        if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK)
        {
            std::cerr << "Cannot initialize CURL.\n";

            return;
        }

        httplib::Server http_server;

        http_server.set_post_routing_handler(
            [](
                const httplib::Request &request ,
                httplib::Response &response
            )
            {
                if (request.has_header("Origin"))
                {
                    const std::string origin =
                        request.get_header_value("Origin");

                    if (
                        origin == "http://localhost:5173" ||
                        origin == "http://127.0.0.1:5173"
                    )
                    {
                        response.set_header(
                            "Access-Control-Allow-Origin",
                            origin
                        );
                    }
                }

                response.set_header(
                    "Access-Control-Allow-Methods",
                    "GET, POST, OPTIONS"
                );

                response.set_header(
                    "Access-Control-Allow-Headers",
                    "Content-Type"
                );
            }
        );

        http_server.Options(
            "/api/chat",
            [](
                const httplib::Request & ,
                httplib::Response &response
            )
            {
                response.status = 204;
            }
        );

        http_server.Get(
            "/api/health",
            [](
                const httplib::Request & ,
                httplib::Response &response
            )
            {
                response.set_content(
                    R"({"status":"ok","message":"AIOffice backend is running"})",
                    "application/json"
                );
            }
        );

        http_server.Post(
            "/api/chat",
            [&](
                const httplib::Request &request ,
                httplib::Response &response
            )
            {
                json body = json::parse(
                    request.body ,
                    nullptr ,
                    false
                );

                if (
                    body.is_discarded() ||
                    !body.is_object() ||
                    !body.contains("message") ||
                    !body["message"].is_string()
                )
                {
                    response.status = 400;

                    response.set_content(
                        R"({"error":"Invalid request body"})",
                        "application/json"
                    );

                    return;
                }

                std::string message =
                    body["message"].get<std::string>();

                if (
                    message.find_first_not_of(" \t\n\r") ==
                    std::string::npos
                )
                {
                    response.status = 400;

                    response.set_content(
                        R"({"error":"Message cannot be empty"})",
                        "application/json"
                    );

                    return;
                }

                if (!groq_available && !openrouter_available)
                {
                    response.status = 503;

                    response.set_content(
                        R"({"error":"No AI provider is configured"})",
                        "application/json"
                    );

                    return;
                }

                std::string reply;
                std::string provider_name;
                std::string model_name;

                if (groq_available)
                {
                    provider_name = "groq";
                    model_name = models[0]->_return_model();

                    reply = models[0]->_ask(json(message));
                }

                if (
                    _is_error(reply) &&
                    openrouter_available
                )
                {
                    provider_name = "openrouter";

                    model_name =
                        models[openrouter_start]->_return_model();

                    reply = models[openrouter_start]->_ask(
                        json(message)
                    );
                }
                else if (!groq_available && openrouter_available)
                {
                    provider_name = "openrouter";

                    model_name =
                        models[openrouter_start]->_return_model();

                    reply = models[openrouter_start]->_ask(
                        json(message)
                    );
                }

                if (_is_error(reply))
                {
                    response.status = 502;

                    response.set_content(
                        json({
                            {"error" , reply},
                            {"provider" , provider_name},
                            {"model" , model_name}
                        }).dump(),
                        "application/json"
                    );

                    return;
                }

                response.set_content(
                    json({
                        {"reply" , reply},
                        {"provider" , provider_name},
                        {"model" , model_name}
                    }).dump(),
                    "application/json"
                );
            }
        );

        std::cout
            << "HTTP server running at http://127.0.0.1:8080\n";

        if (!http_server.listen("127.0.0.1" , 8080))
        {
            std::cerr << "Failed to start HTTP server.\n";
        }

        curl_global_cleanup();
    }
}
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

    void _start(ChatHandler chat_handler)
    {
        if (!chat_handler)
        {
            std::cerr << "Chat handler is not configured.\n";

            return;
        }

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
            [&chat_handler](
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

                std::string reply;

                try
                {
                    reply = chat_handler(message);
                }
                catch (const std::exception &error)
                {
                    std::cerr
                        << "[HTTP] Chat handler error: "
                        << error.what()
                        << std::endl;

                    response.status = 500;

                    response.set_content(
                        json({
                            {"error", "Internal server error"}
                        }).dump(),
                        "application/json"
                    );

                    return;
                }
                catch (...)
                {
                    std::cerr
                        << "[HTTP] Unknown chat handler error."
                        << std::endl;

                    response.status = 500;

                    response.set_content(
                        R"({"error":"Internal server error"})",
                        "application/json"
                    );

                    return;
                }

                if (_is_error(reply))
                {
                    response.status = 502;

                    response.set_content(
                        json({
                            {"error", reply},
                            {"provider", "multi-agent"},
                            {"model", "AIOffice"}
                        }).dump(),
                        "application/json"
                    );

                    return;
                }

                response.set_content(
                    json({
                        {"reply", reply},
                        {"provider", "multi-agent"},
                        {"model", "AIOffice"}
                    }).dump(),
                    "application/json"
                );
            }
        );

        std::cout
            << "HTTP server running at http://127.0.0.1:8080"
            << std::endl;

        if (!http_server.listen("127.0.0.1" , 8080))
        {
            std::cerr
                << "Failed to start HTTP server."
                << std::endl;
        }

        curl_global_cleanup();
    }
}
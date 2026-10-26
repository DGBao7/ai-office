#include "providers/GroqProvider.h"

namespace providers
{
    using json = nlohmann::json;

    static size_t _write_callback(
        char *data ,
        size_t size ,
        size_t count ,
        std::string *response
    )
    {
        response -> append(data , size * count);

        return size * count;
    }

    Groq::Groq(
        utils::Env &env ,
        std::string key ,
        std::string model
    )
        : Provider(env , key , model)
    {}

    std::string Groq::_ask(nlohmann::json question)
    {
        if (api_key.empty())
        {
            return "Error: GROQ_API_KEY is empty.";
        }

        CURL *curl = curl_easy_init();

        if (curl == nullptr)
        {
            return "Error: Cannot initialize CURL.";
        }

        json request = {
            {"model", model},
            {"messages", json::array({
                {
                    {"role", "user"},
                    {"content", question}
                }
            })}
        };

        std::string request_body = request.dump();
        std::string response;

        struct curl_slist *headers = nullptr;

        headers = curl_slist_append(
            headers ,
            "Content-Type: application/json"
        );

        std::string auth_header = "Authorization: Bearer " + api_key;

        headers = curl_slist_append(
            headers ,
            auth_header.c_str()
        );

        curl_easy_setopt(
            curl ,
            CURLOPT_URL ,
            "https://api.groq.com/openai/v1/chat/completions"
        );

        curl_easy_setopt(curl , CURLOPT_HTTPHEADER , headers);
        curl_easy_setopt(curl , CURLOPT_POST , 1L);

        curl_easy_setopt(
            curl ,
            CURLOPT_POSTFIELDS ,
            request_body.c_str()
        );

        curl_easy_setopt(curl , CURLOPT_WRITEFUNCTION , _write_callback);
        curl_easy_setopt(curl , CURLOPT_WRITEDATA , &response);
        curl_easy_setopt(curl , CURLOPT_TIMEOUT , 60L);

        CURLcode result = curl_easy_perform(curl);

        long status_code = 0;

        curl_easy_getinfo(
            curl ,
            CURLINFO_RESPONSE_CODE ,
            &status_code
        );

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (result != CURLE_OK)
        {
            return std::string("CURL error: ") +
                   curl_easy_strerror(result);
        }

        try
        {
            json data = json::parse(response);

            if (status_code < 200 || status_code >= 300)
            {
                if (data.contains("error"))
                {
                    if (data["error"].is_object() &&
                        data["error"].contains("message"))
                    {
                        return "Groq API error: " +
                            data["error"]["message"].get<std::string>();
                    }
                }

                return "Groq HTTP error: " +
                       std::to_string(status_code);
            }

            return data
                .at("choices")
                .at(0)
                .at("message")
                .at("content")
                .get<std::string>();
        }
        catch (const std::exception &error)
        {
            return std::string("Response parsing error: ") +
                   error.what();
        }
    }
}
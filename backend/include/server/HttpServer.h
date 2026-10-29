#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "server/httplib.h"

#include "providers/Initializer.h"

#include "utils/Env.h"
#include "utils/Json.h"

#include "contact/Memory.h"

#include <curl/curl.h>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <mutex>
#include <functional>
#include <cstdlib>

namespace server
{
    using ChatHandler = std::function<std::string(const std::string &)>;

    void _start(ChatHandler chat_handler);
}

#endif
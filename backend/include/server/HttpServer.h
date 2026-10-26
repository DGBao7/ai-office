#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "server/httplib.h"

#include "providers/Initializer.h"

#include "utils/Env.h"
#include "utils/Json.h"

#include <curl/curl.h>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace server
{
    void _start();
}

#endif
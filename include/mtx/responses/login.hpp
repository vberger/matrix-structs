#pragma once

#include <json.hpp>
#include <regex>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace responses {
struct Login
{
        // The fully-qualified Matrix ID that has been registered.
        mtx::identifiers::User user_id;
        // An access token for the account.
        // This access token can then be used to authorize other requests.
        std::string access_token;
        // The hostname of the homeserver on which the account has been registered.
        std::string home_server;
        // ID of the logged-in device.
        // Will be the same as the corresponding parameter in the request, if one was specified.
        std::string device_id;
};

void
from_json(const json &obj, Login &response)
{
        using namespace mtx::identifiers;
        response.user_id = parse<User>(obj.at("user_id").get<std::string>());

        response.access_token = obj.at("access_token").get<std::string>();
        response.home_server  = obj.at("home_server").get<std::string>();

        if (obj.count("device_id") != 0)
                response.device_id = obj.at("device_id").get<std::string>();
}
}
}

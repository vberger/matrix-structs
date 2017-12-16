#pragma once

#include <string>

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace requests {

enum class Visibility
{
        Private,
        Public,
};

enum class Preset
{
        PrivateChat,
        PublicChat,
        TrustedPrivateChat,
};

struct CreateRoom
{
        std::string name;
        std::string topic;
        std::string room_alias_name;

        std::vector<std::string> invite;
        bool is_direct = false;

        Preset preset         = Preset::PrivateChat;
        Visibility visibility = Visibility::Private;
};

void
to_json(json &obj, const CreateRoom &request);
}
}

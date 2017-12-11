#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace requests {

enum class Visibility
{
        Private,
        Public,
};

inline std::string
visibilityToString(Visibility visibility)
{
        if (visibility == Visibility::Private) {
                return "private";
        }

        return "public";
}

enum class Preset
{
        PrivateChat,
        PublicChat,
        TrustedPrivateChat,
};

inline std::string
presetToString(Preset preset)
{
        switch (preset) {
        case Preset::PrivateChat:
                return "private_chat";
                break;
        case Preset::PublicChat:
                return "public_chat";
                break;
        case Preset::TrustedPrivateChat:
                return "trusted_private_chat";
                break;
        }

        return "private_chat";
}

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

inline void
to_json(json &obj, const CreateRoom &request)
{
        if (!request.name.empty())
                obj["name"] = request.name;

        if (!request.topic.empty())
                obj["topic"] = request.topic;

        if (!request.room_alias_name.empty())
                obj["room_alias_name"] = request.room_alias_name;

        if (request.invite.size() != 0)
                obj["invite"] = request.invite;

        obj["is_direct"]  = request.is_direct;
        obj["preset"]     = presetToString(request.preset);
        obj["visibility"] = visibilityToString(request.visibility);
}
}
}

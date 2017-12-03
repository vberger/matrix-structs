#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace msg {

struct Emote
{
        // The emote action to perform.
        std::string body;
        // Must be 'm.emote'.
        std::string msgtype;
};

inline void
from_json(const json &obj, Emote &content)
{
        content.body    = obj.at("body").get<std::string>();
        content.msgtype = obj.at("msgtype").get<std::string>();
}

inline void
to_json(json &obj, const Emote &content)
{
        obj["msgtype"] = "m.emote";
        obj["body"]    = content.body;
}

} // namespace msg
} // namespace events
} // namespace mtx

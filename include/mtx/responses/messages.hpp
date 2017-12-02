#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace responses {
struct Messages
{
        std::string start;
        std::string end;
        std::vector<events::collections::TimelineEvents> chunk;
};

void
from_json(const json &obj, Messages &messages)
{
        messages.start = obj.at("start").get<std::string>();
        messages.end   = obj.at("end").get<std::string>();

        utils::parse_timeline_events(obj.at("chunk"), messages.chunk);
}
}
}

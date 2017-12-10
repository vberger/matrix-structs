#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Topic
{
        std::string topic;
};

inline void
from_json(const json &obj, Topic &event)
{
        if (is_spec_violation(obj, "topic", "m.room.topic"))
                return;

        event.topic = obj.at("topic").get<std::string>();
}

inline void
to_json(json &obj, const Topic &event)
{
        obj["topic"] = event.topic;
}

} // namespace state
} // namespace events
} // namespace mtx

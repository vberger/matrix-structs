#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct PinnedEvents
{
        std::vector<std::string> pinned;
};

inline void
from_json(const json &obj, PinnedEvents &event)
{
        if (is_spec_violation(obj, "pinned", "m.room.pinned_events"))
                return;

        event.pinned = obj.at("pinned").get<std::vector<std::string>>();
}

inline void
to_json(json &obj, const PinnedEvents &event)
{
        obj["pinned"] = event.pinned;
}

} // namespace state
} // namespace events
} // namespace mtx

#include <json.hpp>
#include <string>

#include "mtx/events/name.hpp"
#include "mtx/macros.hpp"

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

void
from_json(const json &obj, Name &event)
{
        if (is_spec_violation(obj, "name", "m.room.name"))
                return;

        event.name = obj.at("name").get<std::string>();
}

void
to_json(json &obj, const Name &event)
{
        obj["name"] = event.name;
}

} // namespace state
} // namespace events
} // namespace mtx

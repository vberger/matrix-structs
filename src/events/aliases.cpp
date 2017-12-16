#include <json.hpp>

using json = nlohmann::json;

#include "mtx/events/aliases.hpp"
#include "mtx/macros.hpp"

namespace mtx {
namespace events {
namespace state {

void
from_json(const json &obj, Aliases &content)
{
        if (is_spec_violation(obj, "aliases", "m.room.aliases"))
                return;

        content.aliases = obj.at("aliases").get<std::vector<std::string>>();
}

void
to_json(json &obj, const Aliases &content)
{
        obj["aliases"] = content.aliases;
}

} // namespace state
} // namespace events
} // namespace mtx

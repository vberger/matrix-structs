#include <json.hpp>
#include <string>

#include "mtx/events/redaction.hpp"
#include "mtx/macros.hpp"

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

void
from_json(const json &obj, Redaction &event)
{
        if (is_spec_violation(obj, "reason", "m.room.redaction"))
                return;

        event.reason = obj.at("reason").get<std::string>();
}

void
to_json(json &obj, const Redaction &event)
{
        obj["reason"] = event.reason;
}

} // namespace state
} // namespace events
} // namespace mtx

#include <json.hpp>
#include <string>

#include "mtx/events/guest_access.hpp"
#include "mtx/macros.hpp"

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

std::string
accessStateToString(AccessState state)
{
        if (state == AccessState::CanJoin)
                return "can_join";

        return "forbidden";
}

AccessState
stringToAccessState(const std::string &state)
{
        if (state == "can_join")
                return AccessState::CanJoin;

        return AccessState::Forbidden;
}

void
from_json(const json &obj, GuestAccess &guest_access)
{
        if (is_spec_violation(obj, "guest_access", "m.room.guest_access"))
                return;

        guest_access.guest_access = stringToAccessState(obj.at("guest_access").get<std::string>());
}

void
to_json(json &obj, const GuestAccess &guest_access)
{
        obj["guest_access"] = accessStateToString(guest_access.guest_access);
}

} // namespace state
} // namespace events
} // namespace mtx

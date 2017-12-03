#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

enum class AccessState
{
        CanJoin,
        Forbidden,
};

inline std::string
accessStateToString(AccessState state)
{
        if (state == AccessState::CanJoin)
                return "can_join";

        return "forbidden";
}

inline AccessState
stringToAccessState(const std::string &state)
{
        if (state == "can_join")
                return AccessState::CanJoin;

        return AccessState::Forbidden;
}

struct GuestAccess
{
        AccessState guest_access = AccessState::Forbidden;
};

inline void
from_json(const json &obj, GuestAccess &guest_access)
{
        guest_access.guest_access = stringToAccessState(obj.at("guest_access").get<std::string>());
}

inline void
to_json(json &obj, const GuestAccess &guest_access)
{
        obj["guest_access"] = accessStateToString(guest_access.guest_access);
}

} // namespace state
} // namespace events
} // namespace mtx

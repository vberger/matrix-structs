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

std::string
accessStateToString(AccessState state);

AccessState
stringToAccessState(const std::string &state);

struct GuestAccess
{
        AccessState guest_access = AccessState::Forbidden;
};

void
from_json(const json &obj, GuestAccess &guest_access);

void
to_json(json &obj, const GuestAccess &guest_access);

} // namespace state
} // namespace events
} // namespace mtx

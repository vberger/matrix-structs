#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

enum class Membership
{
        // The user has joined.
        Join,
        // The user has been invited.
        Invite,
        // The user is banned.
        Ban,
        // The user has left.
        Leave,
        // The user has requested to join.
        Knock,
};

std::string
membershipToString(const Membership &membership);

Membership
stringToMembership(const std::string &membership);

struct Member
{
        Membership membership;
        std::string avatar_url;
        std::string display_name;

        /* ThirdPartyInvite third_party_invite; */
        bool is_direct = false;
};

void
from_json(const json &obj, Member &member);

void
to_json(json &obj, const Member &member);

} // namespace state
} // namespace events
} // namespace mtx

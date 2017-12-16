#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

constexpr uint16_t EventsDefault = 0;
constexpr uint16_t UsersDefault  = 0;
constexpr uint16_t StatesDefault = 50;

constexpr uint16_t User      = 0;
constexpr uint16_t Moderator = 50;
constexpr uint16_t Admin     = 100;

struct PowerLevels
{
        int eventLevel(std::string event_type) const;
        int userLevel(std::string user_id) const;

        uint16_t ban    = Moderator;
        uint16_t invite = Moderator;
        uint16_t kick   = Moderator;
        uint16_t redact = Moderator;

        uint16_t events_default = User;
        uint16_t users_default  = User;
        uint16_t state_default  = Moderator;

        std::map<std::string, uint16_t> events;
        std::map<std::string, uint16_t> users;
};

void
from_json(const json &obj, PowerLevels &power_levels);

void
to_json(json &obj, const PowerLevels &power_levels);

} // namespace state
} // namespace events
} // namespace mtx

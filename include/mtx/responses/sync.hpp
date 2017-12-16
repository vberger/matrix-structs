#pragma once

#include <map>
#include <string>
#include <vector>

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace responses {

struct State
{
        std::vector<events::collections::StateEvents> events;
};

void
from_json(const json &obj, State &state);

struct Timeline
{
        std::vector<events::collections::TimelineEvents> events;
        std::string prev_batch;
        bool limited = false;
};

void
from_json(const json &obj, Timeline &timeline);

struct UnreadNotifications
{
        uint16_t highlight_count    = 0;
        uint16_t notification_count = 0;
};

void
from_json(const json &obj, UnreadNotifications &notifications);

struct Ephemeral
{
        std::vector<std::string> typing;
};

void
from_json(const json &obj, Ephemeral &ephemeral);

struct JoinedRoom
{
        State state;
        Timeline timeline;
        UnreadNotifications unread_notifications;
        /* AccountData account_data; */
        Ephemeral ephemeral;
};

void
from_json(const json &obj, JoinedRoom &room);

struct LeftRoom
{
        State state;
        Timeline timeline;
};

void
from_json(const json &obj, LeftRoom &room);

struct InvitedRoom
{
        std::vector<events::collections::StrippedEvents> invite_state;
};

void
from_json(const json &obj, InvitedRoom &room);

struct Rooms
{
        std::map<std::string, JoinedRoom> join;
        std::map<std::string, LeftRoom> leave;
        std::map<std::string, InvitedRoom> invite;
};

void
from_json(const json &obj, Rooms &rooms);

struct Sync
{
        std::string next_batch;
        Rooms rooms;
        /* ToDevice to_device; */
        /* Presence presence; */
        /* Groups groups; */
        /* DeviceList device_list; */
        /* AccountData account_data; */
};

void
from_json(const json &obj, Sync &response);
}
}

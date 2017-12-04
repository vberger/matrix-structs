#pragma once

#include <json.hpp>

#include "../events/collections.hpp"

#include <map>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace mtx {
namespace responses {

struct State
{
        std::vector<events::collections::StateEvents> events;
};

inline void
from_json(const json &obj, State &state)
{
        utils::parse_state_events(obj.at("events"), state.events);
}

struct Timeline
{
        std::vector<events::collections::TimelineEvents> events;
        std::string prev_batch;
        bool limited = false;
};

inline void
from_json(const json &obj, Timeline &timeline)
{
        timeline.prev_batch = obj.at("prev_batch").get<std::string>();
        timeline.limited    = obj.at("limited").get<bool>();

        utils::parse_timeline_events(obj.at("events"), timeline.events);
}

struct UnreadNotifications
{
        uint16_t highlight_count    = 0;
        uint16_t notification_count = 0;
};

inline void
from_json(const json &obj, UnreadNotifications &notifications)
{
        if (obj.find("highlight_count") != obj.end())
                notifications.highlight_count = obj.at("highlight_count").get<uint16_t>();

        if (obj.find("notification_count") != obj.end())
                notifications.notification_count = obj.at("notification_count").get<uint16_t>();
}

struct Ephemeral
{
        std::vector<std::string> typing;
};

inline void
from_json(const json &obj, Ephemeral &ephemeral)
{
        if (obj.count("events") == 0)
                return;

        auto events = obj.at("events");

        for (auto event : events) {
                auto type = event.at("type").get<std::string>();

                if (type == "m.typing") {
                        auto content     = event.at("content");
                        ephemeral.typing = content.at("user_ids").get<std::vector<std::string>>();
                }
        }
}

struct JoinedRoom
{
        State state;
        Timeline timeline;
        UnreadNotifications unread_notifications;
        /* AccountData account_data; */
        Ephemeral ephemeral;
};

inline void
from_json(const json &obj, JoinedRoom &room)
{
        room.state    = obj.at("state").get<State>();
        room.timeline = obj.at("timeline").get<Timeline>();

        if (obj.find("unread_notifications") != obj.end())
                room.unread_notifications =
                  obj.at("unread_notifications").get<UnreadNotifications>();

        if (obj.find("ephemeral") != obj.end())
                room.ephemeral = obj.at("ephemeral").get<Ephemeral>();
}

struct LeftRoom
{
        State state;
        Timeline timeline;
};

inline void
from_json(const json &obj, LeftRoom &room)
{
        room.state    = obj.at("state").get<State>();
        room.timeline = obj.at("timeline").get<Timeline>();
}

struct InvitedRoom
{
        State state;
        Timeline timeline;
};

inline void
from_json(const json &obj, InvitedRoom &room)
{
        room.state    = obj.at("state").get<State>();
        room.timeline = obj.at("timeline").get<Timeline>();
}

struct Rooms
{
        std::map<std::string, JoinedRoom> join;
        std::map<std::string, LeftRoom> leave;
        std::map<std::string, InvitedRoom> invite;
};

inline void
from_json(const json &obj, Rooms &rooms)
{
        if (obj.count("join") != 0) {
                auto joined = obj.at("join");

                for (auto it = joined.begin(); it != joined.end(); ++it)
                        rooms.join[it.key()] = it.value().get<JoinedRoom>();
        }

        if (obj.count("leave") != 0) {
                auto leave = obj.at("leave");

                for (auto it = leave.begin(); it != leave.end(); ++it)
                        rooms.leave[it.key()] = it.value().get<LeftRoom>();
        }

        if (obj.count("invite") != 0) {
                auto invite = obj.at("invite");

                for (auto it = invite.begin(); it != invite.end(); ++it)
                        rooms.invite[it.key()] = it.value().get<InvitedRoom>();
        }
}

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

inline void
from_json(const json &obj, Sync &response)
{
        response.rooms      = obj.at("rooms").get<Rooms>();
        response.next_batch = obj.at("next_batch").get<std::string>();
}
}
}

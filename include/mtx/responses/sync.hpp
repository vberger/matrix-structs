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

void
from_json(const json &obj, State &state)
{
        state.events.clear();

        const auto arr = obj.at("events");

        for (const auto &e : arr) {
                events::EventType type = mtx::events::getEventType(e);

                namespace ns = mtx::events::state;

                switch (type) {
                case events::EventType::RoomAliases: {
                        events::StateEvent<ns::Aliases> alias = e;
                        state.events.emplace_back(alias);
                        break;
                }
                case events::EventType::RoomAvatar: {
                        events::StateEvent<ns::Avatar> avatar = e;
                        state.events.emplace_back(avatar);
                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        events::StateEvent<ns::CanonicalAlias> canonical_alias = e;
                        state.events.emplace_back(canonical_alias);
                        break;
                }
                case events::EventType::RoomCreate: {
                        events::StateEvent<ns::Create> create = e;
                        state.events.emplace_back(create);
                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        events::StateEvent<ns::HistoryVisibility> history_visibility = e;
                        state.events.emplace_back(history_visibility);
                        break;
                }
                case events::EventType::RoomJoinRules: {
                        events::StateEvent<ns::JoinRules> join_rules = e;
                        state.events.emplace_back(join_rules);
                        break;
                }
                case events::EventType::RoomMember: {
                        events::StateEvent<ns::Member> member = e;
                        state.events.emplace_back(member);
                        break;
                }
                case events::EventType::RoomName: {
                        events::StateEvent<ns::Name> name = e;
                        state.events.emplace_back(name);
                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        events::StateEvent<ns::PowerLevels> power_levels = e;
                        state.events.emplace_back(power_levels);
                        break;
                }
                case events::EventType::RoomTopic: {
                        events::StateEvent<ns::Topic> topic = e;
                        state.events.emplace_back(topic);
                        break;
                }
                default:
                        std::cout << "Skipping unknown event " << e << std::endl;
                        continue;
                }
        }
}

struct Timeline
{
        std::vector<events::collections::TimelineEvents> events;
        std::string prev_batch;
        bool limited = false;
};

void
from_json(const json &obj, Timeline &timeline)
{
        timeline.prev_batch = obj.at("prev_batch").get<std::string>();
        timeline.limited    = obj.at("limited").get<bool>();

        timeline.events.clear();

        /* const auto events = obj.at("events"); */

        /* for (const auto &event : events) { */
        /*         events::EventType type = mtx::events::getEventType(event); */

        /*         namespace ns = mtx::events::state; */

        /*         switch (type) { */
        /*         default: */
        /*                 // TODO handle the state events the room messages. */
        /*                 continue; */
        /*         } */
        /* } */
}

struct UnreadNotifications
{
        uint16_t highlight_count    = 0;
        uint16_t notification_count = 0;
};

void
from_json(const json &obj, UnreadNotifications &notifications)
{
        if (obj.find("highlight_count") != obj.end())
                notifications.highlight_count = obj.at("highlight_count").get<uint16_t>();

        if (obj.find("notification_count") != obj.end())
                notifications.notification_count = obj.at("notification_count").get<uint16_t>();
}

struct JoinedRoom
{
        State state;
        Timeline timeline;
        /* AccountData account_data; */
        UnreadNotifications unread_notifications;
        std::vector<std::string> typing_user_ids; // TODO: this isn't the name of they key.
};

void
from_json(const json &obj, JoinedRoom &room)
{
        room.state    = obj.at("state").get<State>();
        room.timeline = obj.at("timeline").get<Timeline>();

        if (obj.find("unread_notifications") != obj.end())
                room.unread_notifications =
                  obj.at("unread_notifications").get<UnreadNotifications>();
}

struct LeftRoom
{
        State state;
        Timeline timeline;
};

void
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

void
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

void
from_json(const json &obj, Rooms &rooms)
{
        auto joined = obj.at("join");
        auto leave  = obj.at("leave");
        auto invite = obj.at("invite");

        for (auto it = joined.begin(); it != joined.end(); ++it)
                rooms.join[it.key()] = it.value().get<JoinedRoom>();

        for (auto it = leave.begin(); it != leave.end(); ++it)
                rooms.leave[it.key()] = it.value().get<LeftRoom>();

        for (auto it = invite.begin(); it != invite.end(); ++it)
                rooms.invite[it.key()] = it.value().get<InvitedRoom>();
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

void
from_json(const json &obj, Sync &response)
{
        response.rooms      = obj.at("rooms").get<Rooms>();
        response.next_batch = obj.at("next_batch").get<std::string>();
}
}
}

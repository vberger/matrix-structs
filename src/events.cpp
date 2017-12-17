#include "mtx/events.hpp"

using json = nlohmann::json;

namespace mtx {
namespace events {

EventType
getEventType(const std::string &type)
{
        if (type == "m.room.aliases")
                return EventType::RoomAliases;
        else if (type == "m.room.avatar")
                return EventType::RoomAvatar;
        else if (type == "m.room.canonical_alias")
                return EventType::RoomCanonicalAlias;
        else if (type == "m.room.create")
                return EventType::RoomCreate;
        else if (type == "m.room.guest_access")
                return EventType::RoomGuestAccess;
        else if (type == "m.room.history_visibility")
                return EventType::RoomHistoryVisibility;
        else if (type == "m.room.join_rules")
                return EventType::RoomJoinRules;
        else if (type == "m.room.member")
                return EventType::RoomMember;
        else if (type == "m.room.message")
                return EventType::RoomMessage;
        else if (type == "m.room.name")
                return EventType::RoomName;
        else if (type == "m.room.power_levels")
                return EventType::RoomPowerLevels;
        else if (type == "m.room.topic")
                return EventType::RoomTopic;
        else if (type == "m.room.redaction")
                return EventType::RoomRedaction;
        else if (type == "m.room.pinned_events")
                return EventType::RoomPinnedEvents;

        return EventType::Unsupported;
}

EventType
getEventType(const json &obj)
{
        if (obj.find("type") != obj.end())
                return getEventType(obj.at("type").get<std::string>());

        return EventType::Unsupported;
}

MessageType
getMessageType(const std::string &type)
{
        if (type == "m.audio")
                return MessageType::Audio;
        else if (type == "m.emote")
                return MessageType::Emote;
        else if (type == "m.file")
                return MessageType::File;
        else if (type == "m.image")
                return MessageType::Image;
        else if (type == "m.location")
                return MessageType::Location;
        else if (type == "m.notice")
                return MessageType::Notice;
        else if (type == "m.text")
                return MessageType::Text;
        else if (type == "m.video")
                return MessageType::Video;

        return MessageType::Unknown;
}

MessageType
getMessageType(const json &obj)
{
        if (obj.is_null())
                return MessageType::Unknown;

        if (obj.find("msgtype") == obj.end())
                return MessageType::Unknown;

        return getMessageType(obj.at("msgtype").get<std::string>());
}
}
}

#include "mtx/responses/common.hpp"

#include "mtx/events.hpp"
#include "mtx/events/aliases.hpp"
#include "mtx/events/avatar.hpp"
#include "mtx/events/canonical_alias.hpp"
#include "mtx/events/create.hpp"
#include "mtx/events/guest_access.hpp"
#include "mtx/events/history_visibility.hpp"
#include "mtx/events/join_rules.hpp"
#include "mtx/events/member.hpp"
#include "mtx/events/name.hpp"
#include "mtx/events/pinned_events.hpp"
#include "mtx/events/power_levels.hpp"
#include "mtx/events/redaction.hpp"
#include "mtx/events/topic.hpp"

#include <iostream>

using json = nlohmann::json;

namespace mtx {
namespace responses {
namespace utils {

inline void
log_error(json::exception &err, const json &event)
{
        std::cout << err.what() << std::endl;
        std::cout << event.dump(2) << std::endl;
}

inline void
log_error(std::string err, const json &event)
{
        std::cout << err << std::endl;
        std::cout << event.dump(2) << std::endl;
}

void
parse_timeline_events(const json &events,
                      std::vector<mtx::events::collections::TimelineEvents> &container)
{
        container.clear();

        for (const auto &e : events) {
                namespace ns = mtx::events::state;

                events::EventType type = mtx::events::getEventType(e);

                if (type == events::EventType::Unsupported) {
                        // TODO enable on debug builds
                        /* log_error("Invalid event type", e); */
                        continue;
                }

                switch (type) {
                case events::EventType::RoomAliases: {
                        try {
                                events::StateEvent<ns::Aliases> alias = e;
                                container.emplace_back(alias);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomAvatar: {
                        try {
                                events::StateEvent<ns::Avatar> avatar = e;
                                container.emplace_back(avatar);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        try {
                                events::StateEvent<ns::CanonicalAlias> canonical_alias = e;
                                container.emplace_back(canonical_alias);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomCreate: {
                        try {
                                events::StateEvent<ns::Create> create = e;
                                container.emplace_back(create);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomGuestAccess: {
                        try {
                                events::StateEvent<ns::GuestAccess> guest_access = e;
                                container.emplace_back(guest_access);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        try {
                                events::StateEvent<ns::HistoryVisibility> history_visibility = e;
                                container.emplace_back(history_visibility);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomJoinRules: {
                        try {
                                events::StateEvent<ns::JoinRules> join_rules = e;
                                container.emplace_back(join_rules);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomMember: {
                        try {
                                events::StateEvent<ns::Member> member = e;
                                container.emplace_back(member);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomName: {
                        try {
                                events::StateEvent<ns::Name> name = e;
                                container.emplace_back(name);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        try {
                                events::StateEvent<ns::PowerLevels> power_levels = e;
                                container.emplace_back(power_levels);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomRedaction: {
                        try {
                                events::RoomEvent<mtx::events::msg::Redaction> redaction = e;
                                container.emplace_back(redaction);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomTopic: {
                        try {
                                events::StateEvent<ns::Topic> topic = e;
                                container.emplace_back(topic);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomMessage: {
                        using MsgType = mtx::events::MessageType;

                        MsgType msg_type = mtx::events::getMessageType(e.at("content"));

                        if (msg_type == events::MessageType::Unknown) {
                                log_error("Invalid event type", e);
                                continue;
                        }

                        switch (msg_type) {
                        case MsgType::Audio: {
                                try {
                                        events::RoomEvent<events::msg::Audio> audio = e;
                                        container.emplace_back(audio);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        case MsgType::Emote: {
                                try {
                                        events::RoomEvent<events::msg::Emote> emote = e;
                                        container.emplace_back(emote);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        case MsgType::File: {
                                try {
                                        events::RoomEvent<events::msg::File> file = e;
                                        container.emplace_back(file);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        case MsgType::Image: {
                                try {
                                        events::RoomEvent<events::msg::Image> image = e;
                                        container.emplace_back(image);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        case MsgType::Location: {
                                /* events::RoomEvent<events::msg::Location> location = e; */
                                /* container.emplace_back(location); */
                                break;
                        }
                        case MsgType::Notice: {
                                try {
                                        events::RoomEvent<events::msg::Notice> notice = e;
                                        container.emplace_back(notice);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        case MsgType::Text: {
                                try {
                                        events::RoomEvent<events::msg::Text> text = e;
                                        container.emplace_back(text);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        case MsgType::Video: {
                                try {
                                        events::RoomEvent<events::msg::Video> video = e;
                                        container.emplace_back(video);
                                } catch (json::exception &err) {
                                        log_error(err, e);
                                }

                                break;
                        }
                        default:
                                continue;
                        }
                        break;
                }
                default:
                        continue;
                }
        }
}

void
parse_state_events(const json &events,
                   std::vector<mtx::events::collections::StateEvents> &container)
{
        container.clear();

        for (const auto &e : events) {
                namespace ns           = mtx::events::state;
                events::EventType type = mtx::events::getEventType(e);

                if (type == events::EventType::Unsupported) {
                        // TODO enable on debug build
                        /* log_error("Invalid event type", e); */
                        continue;
                }

                switch (type) {
                case events::EventType::RoomAliases: {
                        try {
                                events::StateEvent<ns::Aliases> alias = e;
                                container.emplace_back(alias);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomAvatar: {
                        try {
                                events::StateEvent<ns::Avatar> avatar = e;
                                container.emplace_back(avatar);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        try {
                                events::StateEvent<ns::CanonicalAlias> canonical_alias = e;
                                container.emplace_back(canonical_alias);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomCreate: {
                        try {
                                events::StateEvent<ns::Create> create = e;
                                container.emplace_back(create);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomGuestAccess: {
                        try {
                                events::StateEvent<ns::GuestAccess> guest_access = e;
                                container.emplace_back(guest_access);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        try {
                                events::StateEvent<ns::HistoryVisibility> history_visibility = e;
                                container.emplace_back(history_visibility);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomJoinRules: {
                        try {
                                events::StateEvent<ns::JoinRules> join_rules = e;
                                container.emplace_back(join_rules);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomMember: {
                        try {
                                events::StateEvent<ns::Member> member = e;
                                container.emplace_back(member);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomName: {
                        try {
                                events::StateEvent<ns::Name> name = e;
                                container.emplace_back(name);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        try {
                                events::StateEvent<ns::PowerLevels> power_levels = e;
                                container.emplace_back(power_levels);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomTopic: {
                        try {
                                events::StateEvent<ns::Topic> topic = e;
                                container.emplace_back(topic);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                default:
                        continue;
                }
        }
}

void
parse_stripped_events(const json &events,
                      std::vector<mtx::events::collections::StrippedEvents> &container)
{
        container.clear();

        for (const auto &e : events) {
                namespace ns           = mtx::events::state;
                events::EventType type = mtx::events::getEventType(e);

                if (type == events::EventType::Unsupported) {
                        // TODO enable on debug builds
                        /* log_error("Invalid event type", e); */
                        continue;
                }

                switch (type) {
                case events::EventType::RoomAliases: {
                        try {
                                events::StrippedEvent<ns::Aliases> alias = e;
                                container.emplace_back(alias);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomAvatar: {
                        try {
                                events::StrippedEvent<ns::Avatar> avatar = e;
                                container.emplace_back(avatar);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        try {
                                events::StrippedEvent<ns::CanonicalAlias> canonical_alias = e;
                                container.emplace_back(canonical_alias);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomCreate: {
                        try {
                                events::StrippedEvent<ns::Create> create = e;
                                container.emplace_back(create);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomGuestAccess: {
                        try {
                                events::StrippedEvent<ns::GuestAccess> guest_access = e;
                                container.emplace_back(guest_access);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        try {
                                events::StrippedEvent<ns::HistoryVisibility> history_visibility = e;
                                container.emplace_back(history_visibility);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomJoinRules: {
                        try {
                                events::StrippedEvent<ns::JoinRules> join_rules = e;
                                container.emplace_back(join_rules);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomMember: {
                        try {
                                events::StrippedEvent<ns::Member> member = e;
                                container.emplace_back(member);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomName: {
                        try {
                                events::StrippedEvent<ns::Name> name = e;
                                container.emplace_back(name);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        try {
                                events::StrippedEvent<ns::PowerLevels> power_levels = e;
                                container.emplace_back(power_levels);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                case events::EventType::RoomTopic: {
                        try {
                                events::StrippedEvent<ns::Topic> topic = e;
                                container.emplace_back(topic);
                        } catch (json::exception &err) {
                                log_error(err, e);
                        }

                        break;
                }
                default:
                        continue;
                }
        }
}
}
}
}

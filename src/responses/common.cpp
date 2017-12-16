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
#include "mtx/events/topic.hpp"

using json = nlohmann::json;

namespace mtx {
namespace responses {
namespace utils {

void
parse_timeline_events(const json &events,
                      std::vector<mtx::events::collections::TimelineEvents> &container)
{
        container.clear();

        for (const auto &e : events) {
                events::EventType type = mtx::events::getEventType(e);

                namespace ns = mtx::events::state;

                switch (type) {
                case events::EventType::RoomAliases: {
                        events::StateEvent<ns::Aliases> alias = e;
                        container.emplace_back(alias);
                        break;
                }
                case events::EventType::RoomAvatar: {
                        events::StateEvent<ns::Avatar> avatar = e;
                        container.emplace_back(avatar);
                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        events::StateEvent<ns::CanonicalAlias> canonical_alias = e;
                        container.emplace_back(canonical_alias);
                        break;
                }
                case events::EventType::RoomCreate: {
                        events::StateEvent<ns::Create> create = e;
                        container.emplace_back(create);
                        break;
                }
                case events::EventType::RoomGuestAccess: {
                        events::StateEvent<ns::GuestAccess> guest_access = e;
                        container.emplace_back(guest_access);
                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        events::StateEvent<ns::HistoryVisibility> history_visibility = e;
                        container.emplace_back(history_visibility);
                        break;
                }
                case events::EventType::RoomJoinRules: {
                        events::StateEvent<ns::JoinRules> join_rules = e;
                        container.emplace_back(join_rules);
                        break;
                }
                case events::EventType::RoomMember: {
                        events::StateEvent<ns::Member> member = e;
                        container.emplace_back(member);
                        break;
                }
                case events::EventType::RoomName: {
                        events::StateEvent<ns::Name> name = e;
                        container.emplace_back(name);
                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        events::StateEvent<ns::PowerLevels> power_levels = e;
                        container.emplace_back(power_levels);
                        break;
                }
                case events::EventType::RoomTopic: {
                        events::StateEvent<ns::Topic> topic = e;
                        container.emplace_back(topic);
                        break;
                }
                case events::EventType::RoomMessage: {
                        auto msg_type = mtx::events::getMessageType(e.at("content"));
                        using MsgType = mtx::events::MessageType;

                        switch (msg_type) {
                        case MsgType::Audio: {
                                events::RoomEvent<events::msg::Audio> audio = e;
                                container.emplace_back(audio);
                                break;
                        }
                        case MsgType::Emote: {
                                events::RoomEvent<events::msg::Emote> emote = e;
                                container.emplace_back(emote);
                                break;
                        }
                        case MsgType::File: {
                                events::RoomEvent<events::msg::File> file = e;
                                container.emplace_back(file);
                                break;
                        }
                        case MsgType::Image: {
                                events::RoomEvent<events::msg::Image> image = e;
                                container.emplace_back(image);
                                break;
                        }
                        case MsgType::Location: {
                                /* events::RoomEvent<events::msg::Location> location = e; */
                                /* container.emplace_back(location); */
                                break;
                        }
                        case MsgType::Notice: {
                                events::RoomEvent<events::msg::Notice> notice = e;
                                container.emplace_back(notice);
                                break;
                        }
                        case MsgType::Text: {
                                events::RoomEvent<events::msg::Text> text = e;
                                container.emplace_back(text);
                                break;
                        }
                        case MsgType::Video: {
                                events::RoomEvent<events::msg::Video> video = e;
                                container.emplace_back(video);
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
                events::EventType type = mtx::events::getEventType(e);

                namespace ns = mtx::events::state;

                switch (type) {
                case events::EventType::RoomAliases: {
                        events::StateEvent<ns::Aliases> alias = e;
                        container.emplace_back(alias);
                        break;
                }
                case events::EventType::RoomAvatar: {
                        events::StateEvent<ns::Avatar> avatar = e;
                        container.emplace_back(avatar);
                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        events::StateEvent<ns::CanonicalAlias> canonical_alias = e;
                        container.emplace_back(canonical_alias);
                        break;
                }
                case events::EventType::RoomCreate: {
                        events::StateEvent<ns::Create> create = e;
                        container.emplace_back(create);
                        break;
                }
                case events::EventType::RoomGuestAccess: {
                        events::StateEvent<ns::GuestAccess> guest_access = e;
                        container.emplace_back(guest_access);
                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        events::StateEvent<ns::HistoryVisibility> history_visibility = e;
                        container.emplace_back(history_visibility);
                        break;
                }
                case events::EventType::RoomJoinRules: {
                        events::StateEvent<ns::JoinRules> join_rules = e;
                        container.emplace_back(join_rules);
                        break;
                }
                case events::EventType::RoomMember: {
                        events::StateEvent<ns::Member> member = e;
                        container.emplace_back(member);
                        break;
                }
                case events::EventType::RoomName: {
                        events::StateEvent<ns::Name> name = e;
                        container.emplace_back(name);
                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        events::StateEvent<ns::PowerLevels> power_levels = e;
                        container.emplace_back(power_levels);
                        break;
                }
                case events::EventType::RoomTopic: {
                        events::StateEvent<ns::Topic> topic = e;
                        container.emplace_back(topic);
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
                events::EventType type = mtx::events::getEventType(e);

                namespace ns = mtx::events::state;

                switch (type) {
                case events::EventType::RoomAliases: {
                        events::StrippedEvent<ns::Aliases> alias = e;
                        container.emplace_back(alias);
                        break;
                }
                case events::EventType::RoomAvatar: {
                        events::StrippedEvent<ns::Avatar> avatar = e;
                        container.emplace_back(avatar);
                        break;
                }
                case events::EventType::RoomCanonicalAlias: {
                        events::StrippedEvent<ns::CanonicalAlias> canonical_alias = e;
                        container.emplace_back(canonical_alias);
                        break;
                }
                case events::EventType::RoomCreate: {
                        events::StrippedEvent<ns::Create> create = e;
                        container.emplace_back(create);
                        break;
                }
                case events::EventType::RoomGuestAccess: {
                        events::StrippedEvent<ns::GuestAccess> guest_access = e;
                        container.emplace_back(guest_access);
                        break;
                }
                case events::EventType::RoomHistoryVisibility: {
                        events::StrippedEvent<ns::HistoryVisibility> history_visibility = e;
                        container.emplace_back(history_visibility);
                        break;
                }
                case events::EventType::RoomJoinRules: {
                        events::StrippedEvent<ns::JoinRules> join_rules = e;
                        container.emplace_back(join_rules);
                        break;
                }
                case events::EventType::RoomMember: {
                        events::StrippedEvent<ns::Member> member = e;
                        container.emplace_back(member);
                        break;
                }
                case events::EventType::RoomName: {
                        events::StrippedEvent<ns::Name> name = e;
                        container.emplace_back(name);
                        break;
                }
                case events::EventType::RoomPowerLevels: {
                        events::StrippedEvent<ns::PowerLevels> power_levels = e;
                        container.emplace_back(power_levels);
                        break;
                }
                case events::EventType::RoomTopic: {
                        events::StrippedEvent<ns::Topic> topic = e;
                        container.emplace_back(topic);
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

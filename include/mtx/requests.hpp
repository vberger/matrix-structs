#pragma once

#include <string>

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace requests {

//! Whether or not the room will be visible by non members.
enum class Visibility
{
        //! A private visibility will hide the room from the published room list.
        Private,
        //! Indicates that the room will be shown in the published room list
        Public,
};

//! Convenience parameter for setting various default state events based on a preset.
enum class Preset
{
        //! `join_rules` is set to `invite`. `history_visibility` is set to `shared`.
        PrivateChat,
        //! `join_rules` is set to `public`. `history_visibility` is set to `shared`.
        PublicChat,
        //! `join_rules` is set to `invite`. `history_visibility` is set to `shared`.
        //! All invitees are given the same power level as the room creator.
        TrustedPrivateChat,
};

//! Request payload for the `POST /_matrix/client/r0/createRoom` endpoint.
struct CreateRoom
{
        //! If this is included, an `m.room.name` event will
        //! be sent into the room to indicate the name of the room.
        std::string name;
        //! If this is included, an `m.room.topic` event will be sent
        //! into the room to indicate the topic for the room.
        std::string topic;
        //! The desired room alias local part. e.g `#foo:example.com`.
        std::string room_alias_name;
        //! A list of user IDs to invite to the room.
        std::vector<std::string> invite;
        //! This flag makes the server set the is_direct flag on the
        //! `m.room.member` events sent to the users in @p invite and @p invite_3pid.
        bool is_direct = false;
        //! Convenience parameter for setting various default state events.
        Preset preset = Preset::PrivateChat;
        //! Whether or not the room will be visible by non members.
        Visibility visibility = Visibility::Private;
};

void
to_json(json &obj, const CreateRoom &request);
}
}

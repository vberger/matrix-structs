#include <gtest/gtest.h>

#include <fstream>

#include <json.hpp>
#include <variant.hpp>

#include <mtx.hpp>

using json = nlohmann::json;

namespace ns = mtx::responses;
namespace me = mtx::events;

TEST(Responses, State)
{
        json data = R"({
	  "events": [
	    { 
	      "unsigned": {
	        "age": 242352,
	        "transaction_id": "txnid"
	      },
	      "content": {
 	        "aliases": [
	          "#somewhere:localhost",
	          "#another:localhost"
	        ]
	      },
	      "event_id": "$WLGTSEFSEF:localhost",
	      "origin_server_ts": 1431961217939,
              "room_id": "!Cuyf34gef24t:localhost",
	      "sender": "@example:localhost",
	      "state_key": "localhost",
	      "type": "m.room.aliases"
	    },
	    { 
	      "unsigned": {
	        "age": 242352,
	        "transaction_id": "txnid"
	      },
	      "content": {
 	        "name": "Random name"
	      },
	      "event_id": "$WLGTSEFSEF2:localhost",
	      "origin_server_ts": 1431961217939,
              "room_id": "!Cuyf34gef24t:localhost",
	      "sender": "@example2:localhost",
	      "state_key": "localhost",
	      "type": "m.room.name"
	    }
	  ]
	})"_json;

        ns::State state = data;

        EXPECT_EQ(state.events.size(), 2);

        auto aliases = mpark::get<me::StateEvent<me::state::Aliases>>(state.events[0]);
        EXPECT_EQ(aliases.event_id, "$WLGTSEFSEF:localhost");
        EXPECT_EQ(aliases.type, me::EventType::RoomAliases);
        EXPECT_EQ(aliases.sender, "@example:localhost");
        EXPECT_EQ(aliases.content.aliases.size(), 2);
        EXPECT_EQ(aliases.content.aliases[0], "#somewhere:localhost");

        auto name = mpark::get<me::StateEvent<me::state::Name>>(state.events[1]);
        EXPECT_EQ(name.event_id, "$WLGTSEFSEF2:localhost");
        EXPECT_EQ(name.type, me::EventType::RoomName);
        EXPECT_EQ(name.sender, "@example2:localhost");
        EXPECT_EQ(name.content.name, "Random name");
}

TEST(Responses, Timeline) {}
TEST(Responses, JoinedRoom) {}
TEST(Responses, LeftRoom) {}

TEST(Responses, Sync)
{
        std::ifstream file("./fixtures/responses/sync.json");

        json data;
        file >> data;

        ns::Sync sync = data;

        EXPECT_EQ(sync.next_batch,
                  "s333358558_324502987_444424_65663508_21685260_193623_2377336_2940807_454");
        EXPECT_EQ(sync.rooms.join.size(), 5);

        auto nheko = sync.rooms.join["!BPvgRcBVHzyFSlYkrg:matrix.org"];
        EXPECT_GT(nheko.state.events.size(), 0);
        EXPECT_GT(nheko.timeline.events.size(), 0);
        EXPECT_EQ(nheko.timeline.limited, true);
        EXPECT_EQ(nheko.timeline.prev_batch,
                  "t10853-333025362_324502987_444424_65663508_21685260_193623_2377336_2940807_454");

        EXPECT_EQ(sync.rooms.leave.size(), 1);
        EXPECT_EQ(sync.rooms.invite.size(), 0);
}

TEST(Responses, Rooms) {}

TEST(Responses, Profile)
{
        json response = R"({
	  "avatar_url": "mxc://matrix.org/SDGdghriugerRg",
	  "displayname": "Alice Margatroid"
        })"_json;

        json null_response = R"({
	  "avatar_url": "mxc://matrix.org/SDGdghriugerRg",
	  "displayname": null
        })"_json;

        json missing_response = R"({
	  "displayname": "Alice Margatroid"
        })"_json;

        json error_response = R"({
	  "displayname": 42
        })"_json;

        ns::Profile profile = response;
        EXPECT_EQ(profile.avatar_url, "mxc://matrix.org/SDGdghriugerRg");
        EXPECT_EQ(profile.display_name, "Alice Margatroid");

        ns::Profile null_profile = null_response;
        EXPECT_EQ(null_profile.avatar_url, "mxc://matrix.org/SDGdghriugerRg");
        EXPECT_EQ(null_profile.display_name, "");

        ns::Profile missing_profile = missing_response;
        EXPECT_EQ(missing_profile.avatar_url, "");
        EXPECT_EQ(missing_profile.display_name, "Alice Margatroid");

        ASSERT_THROW(ns::Profile error_profile = error_response, std::exception);
}

TEST(Responses, Versions)
{
        json data = R"({
	  "versions" : [
	    "r0.0.1",
	    "r0.2.0",
	    "r0.3.0"
	  ]
        })"_json;

        ns::Versions versions = data;
        EXPECT_EQ(versions.versions.size(), 3);
        EXPECT_EQ(versions.versions[0], "r0.0.1");
        EXPECT_EQ(versions.versions[1], "r0.2.0");
        EXPECT_EQ(versions.versions[2], "r0.3.0");

        json error_data = R"({
	  "versions" : [
	    "r.0.0.1"
	  ]
        })"_json;

        ASSERT_THROW(ns::Versions versions = error_data, std::invalid_argument);
}

TEST(Responses, Login)
{
        json data = R"({
          "user_id": "@cheeky_monkey:matrix.org",
          "access_token": "abc123", 
	  "home_server": "matrix.org",
          "device_id": "GHTYAJCE"
        })"_json;

        ns::Login login = data;
        EXPECT_EQ(login.user_id.toString(), "@cheeky_monkey:matrix.org");
        EXPECT_EQ(login.access_token, "abc123");
        EXPECT_EQ(login.home_server, "matrix.org");
        EXPECT_EQ(login.device_id, "GHTYAJCE");

        json data2 = R"({
          "user_id": "@cheeky_monkey:matrix.org",
          "access_token": "abc123", 
	  "home_server": "matrix.org"
        })"_json;

        ns::Login login2 = data2;
        EXPECT_EQ(login2.user_id.toString(), "@cheeky_monkey:matrix.org");
        EXPECT_EQ(login2.access_token, "abc123");
        EXPECT_EQ(login2.home_server, "matrix.org");
        EXPECT_EQ(login2.device_id, "");
}

#include <string>

#include "mtx/events/encrypted.hpp"

static constexpr auto OLM_ALGO = "m.olm.v1.curve25519-aes-sha2";

namespace mtx {
namespace events {
namespace msg {

void
from_json(const json &obj, OlmCipherContent &msg)
{
        msg.body = obj.at("body").get<std::string>();
        msg.type = obj.at("type").get<uint8_t>();
}

void
to_json(json &obj, const OlmCipherContent &msg)
{
        obj["body"] = msg.body;
        obj["type"] = msg.type;
}

void
from_json(const json &obj, OlmEncrypted &msg)
{
        msg.algorithm  = OLM_ALGO;
        msg.sender_key = obj.at("sender_key").get<std::string>();
        msg.ciphertext =
          obj.at("ciphertext").get<std::map<OlmEncrypted::RecipientKey, OlmCipherContent>>();
}

void
to_json(json &obj, const OlmEncrypted &msg)
{
        obj["algorithm"]  = msg.algorithm;
        obj["sender_key"] = msg.sender_key;
        obj["ciphertext"] = msg.ciphertext;
}

void
from_json(const json &obj, Encrypted &content)
{
        content.algorithm  = obj.at("algorithm").get<std::string>();
        content.ciphertext = obj.at("ciphertext").get<std::string>();
        content.device_id  = obj.at("device_id").get<std::string>();
        content.sender_key = obj.at("sender_key").get<std::string>();
        content.session_id = obj.at("session_id").get<std::string>();
}

void
to_json(json &obj, const Encrypted &content)
{
        obj["algorithm"]  = content.algorithm;
        obj["ciphertext"] = content.ciphertext;
        obj["device_id"]  = content.device_id;
        obj["sender_key"] = content.sender_key;
        obj["session_id"] = content.session_id;
}

void
from_json(const json &obj, RoomKey &event)
{
        event.algorithm   = obj.at("algorithm").get<std::string>();
        event.room_id     = obj.at("room_id").get<std::string>();
        event.session_id  = obj.at("session_id").get<std::string>();
        event.session_key = obj.at("session_key").get<std::string>();
}

void
to_json(json &obj, const RoomKey &event)
{
        obj["algorithm"]   = event.algorithm;
        obj["room_id"]     = event.room_id;
        obj["session_id"]  = event.session_id;
        obj["session_key"] = event.session_key;
}

} // namespace msg
} // namespace events
} // namespace mtx

#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

//! Content for the `m.room.redaction` state event.
struct Redaction
{
        //! The reason for the redaction, if any.
        std::string reason;
};

void
from_json(const json &obj, Redaction &event);

void
to_json(json &obj, const Redaction &event);

} // namespace state
} // namespace events
} // namespace mtx

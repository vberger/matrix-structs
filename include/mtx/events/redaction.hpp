#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Redaction
{
        std::string reason;
};

void
from_json(const json &obj, Redaction &event);

void
to_json(json &obj, const Redaction &event);

} // namespace state
} // namespace events
} // namespace mtx

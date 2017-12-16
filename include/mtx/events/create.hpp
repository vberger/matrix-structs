#pragma once

#include <json.hpp>

using json = nlohmann::json;

#include "mtx/identifiers.hpp"

namespace mtx {
namespace events {
namespace state {

struct Create
{
        mtx::identifiers::User creator;
        bool federate;
};

void
from_json(const json &obj, Create &create);

void
to_json(json &obj, const Create &create);

} // namespace state
} // namespace events
} // namespace mtx

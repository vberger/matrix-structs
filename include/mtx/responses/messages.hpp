#pragma once

#include <string>

#include <json.hpp>

#include "mtx/events/collections.hpp"

namespace mtx {
namespace responses {
struct Messages
{
        std::string start;
        std::string end;
        std::vector<mtx::events::collections::TimelineEvents> chunk;
};

void
from_json(const nlohmann::json &obj, Messages &messages);
}
}

#pragma once

#include <json.hpp>

#include <string>
#include <vector>

#include "mtx/events/collections.hpp"

using json = nlohmann::json;

namespace mtx {
namespace responses {
namespace utils {

using TimelineEvents = std::vector<mtx::events::collections::TimelineEvents>;
using StateEvents    = std::vector<mtx::events::collections::StateEvents>;
using StrippedEvents = std::vector<mtx::events::collections::StrippedEvents>;

void
parse_timeline_events(const json &events, TimelineEvents &container);

void
parse_state_events(const json &events, StateEvents &container);

void
parse_stripped_events(const json &events, StrippedEvents &container);
}
}
}

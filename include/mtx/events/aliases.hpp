#pragma once

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct Aliases
{
        std::vector<std::string> aliases;
};

void
from_json(const json &obj, Aliases &content);

void
to_json(json &obj, const Aliases &content);

} // namespace state
} // namespace events
} // namespace mtx

#pragma once

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct CanonicalAlias
{
        std::string alias;
};

void
from_json(const json &obj, CanonicalAlias &canonical_alias);

void
to_json(json &obj, const CanonicalAlias &canonical_alias);

} // namespace state
} // namespace events
} // namespace mtx

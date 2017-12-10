#pragma once

#include <json.hpp>
#include <string>

using json = nlohmann::json;

namespace mtx {
namespace events {
namespace state {

struct CanonicalAlias
{
        std::string alias;
};

inline void
from_json(const json &obj, CanonicalAlias &canonical_alias)
{
        if (is_spec_violation(obj, "alias", "m.room.canonical_alias"))
                return;

        canonical_alias.alias = obj.at("alias").get<std::string>();
}

inline void
to_json(json &obj, const CanonicalAlias &canonical_alias)
{
        obj["alias"] = canonical_alias.alias;
}

} // namespace state
} // namespace events
} // namespace mtx

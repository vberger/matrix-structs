#pragma once

#include <json.hpp>

using json = nlohmann::json;

#include "mtx/events/common.hpp"

namespace mtx {
namespace events {
namespace state {

struct Avatar
{
        mtx::common::ImageInfo image_info;
        std::string url;
};

void
from_json(const json &obj, Avatar &avatar);

void
to_json(json &obj, const Avatar &avatar);

} // namespace state
} // namespace events
} // namespace mtx

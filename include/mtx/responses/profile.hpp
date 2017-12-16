#pragma once

#include <json.hpp>

namespace mtx {
namespace responses {

struct Profile
{
        std::string avatar_url;
        std::string display_name;
};

void
from_json(const nlohmann::json &obj, Profile &profile);
}
}

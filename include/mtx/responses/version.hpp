#pragma once

#include <json.hpp>

namespace mtx {
namespace responses {

struct Versions
{
        std::vector<std::string> versions;
};

void
from_json(const nlohmann::json &obj, Versions &response);
}
}

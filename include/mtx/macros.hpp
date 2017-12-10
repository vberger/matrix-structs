#pragma once

using json = nlohmann::json;

inline bool
is_spec_violation(const json &obj, std::string key, std::string context)
{
        if (obj.count(key) == 0) {
                std::cout << "spec(" << context << "): missing '" << key << "' " << obj
                          << std::endl;
                return true;
        }

        return false;
}

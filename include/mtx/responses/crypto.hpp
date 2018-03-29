#pragma once

#include <json.hpp>

#include "mtx/common.hpp"

#include <map>
#include <string>

namespace mtx {
namespace responses {
//! Response from the `POST /_matrix/client/r0/keys/upload` endpoint.
struct UploadKeys
{
        //! For each key algorithm, the number of unclaimed one-time keys
        //! of that type currently held on the server for this device.
        std::map<std::string, uint32_t> one_time_key_counts;
};

void
from_json(const nlohmann::json &obj, UploadKeys &response);

using DeviceToKeysMap = std::map<std::string, mtx::crypto::DeviceKeys>;

//! Response from the `POST /_matrix/client/r0/keys/query` endpoint.
struct QueryKeys
{
        //! If any remote homeservers could not be reached, they are
        //! recorded here. The names of the properties are the names
        //! of the unreachable servers.
        std::map<std::string, nlohmann::json> failures;
        //! Information on the queried devices.
        //! A map from user ID, to a map from device ID to device information.
        //! For each device, the information returned will be the same
        //! as uploaded via /keys/upload, with the addition of an unsigned property
        std::map<std::string, DeviceToKeysMap> device_keys;
};

void
from_json(const nlohmann::json &obj, QueryKeys &response);

} // namespace responses
} // namespace mtx

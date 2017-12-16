#pragma once

#include <json.hpp>

using json = nlohmann::json;

namespace mtx {
namespace common {

struct ThumbnailInfo
{
        uint64_t h;
        uint64_t w;
        uint64_t size;

        std::string mimetype;
};

void
from_json(const json &obj, ThumbnailInfo &info);

void
to_json(json &obj, const ThumbnailInfo &info);

struct ImageInfo
{
        uint64_t h;
        uint64_t w;
        uint64_t size;

        ThumbnailInfo thumbnail_info;

        std::string thumbnail_url;
        std::string mimetype;
};

void
from_json(const json &obj, ImageInfo &info);

void
to_json(json &obj, const ImageInfo &info);

struct FileInfo
{
        // The size of the file in bytes.
        uint64_t size;
        // Metadata about the image referred to in `thumbnail_url`.
        ThumbnailInfo thumbnail_info;
        // The Matrix URL to the the thumbnail of the file.
        std::string thumbnail_url;
        // The mimetype of the file e.g `application/pdf`.
        std::string mimetype;
};

void
from_json(const json &obj, FileInfo &info);

void
to_json(json &obj, const FileInfo &info);

struct AudioInfo
{
        uint64_t size;
        uint64_t duration;
        std::string mimetype;
};

void
from_json(const json &obj, AudioInfo &info);

void
to_json(json &obj, const AudioInfo &info);

struct VideoInfo
{
        // The size of the video in bytes.
        uint64_t size;
        // The duration of the video in milliseconds.
        uint64_t duration;
        // The height of the video in pixels.
        uint64_t h;
        // The width of the video in pixels.
        uint64_t w;
        // The mimetype of the video e.g. video/mp4.
        std::string mimetype;
        // The URL to an image thumbnail of the video clip.
        std::string thumbnail_url;
        // Metadata about the image referred to in thumbnail_url.
        ThumbnailInfo thumbnail_info;
};

void
from_json(const json &obj, VideoInfo &info);

void
to_json(json &obj, const VideoInfo &info);

} // namespace common
} // namespace mtx

#include <nlohmann/json.hpp>
#include <Eigen/Dense>
#include "submap.h"

nlohmann::json ToJson(const Eigen::Array2Xd& points) {
    nlohmann::json j;
    for (int c = 0; c < points.cols(); ++c) {
      j.push_back(ToJson(points.col(c)));
    }
    return j;
}

template<typename Vec2T>
nlohmann::json ToJson(const Vec2T& vec2) {
    nlohmann::json j;
    j["x"] = vec2.x();
    j["y"] = vec2.y();
    return j;
}


nlohmann::json ToJson(const Submap<uint8_t>& m) {
    nlohmann::json j;
    j["origin"] = ToJson(m.origin());
    j["size"] = ToJson(m.size());
    j["resolution"] = m.resolution();
    for (int x = 0; x < m.size().x(); ++x) {
        for (int y = 0; y < m.size().y(); ++y) {
            j["data"].push_back(m.AtCell({x,y}));
        }
    }
    return j;
}
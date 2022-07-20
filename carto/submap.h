#pragma once

#include <Eigen//Dense>

template<typename T>
class Submap {
    public:
     Submap(const Eigen::Vector2i& sz, const Eigen::Vector2d& origin, double resolution, T init_value = 0) : 
       sz_(sz), origin_(origin), mat_(sz, init_value), r_(resolution) {}
     T AtCell(const Eigen::Vector2i& cell_index) const { return mat_(cell_index.x(), cell_index.y()); }
     //T AtCellOr()
     T AtPointOr(const Eigen::Vector2d& point) const {}
     Eigen::Vector2i CellAt(const Eigen::Vector2d& point) const { return ((point-origin_)/r_).array().floor(); }
     double resolution() const { return r_; }
     Eigen::Vector2d origin() const {return origin_; }
     Eigen::Array2i size() const { return sz_; }
    private:
    Eigen::Array<T, Eigen::Dynamic, Eigen::Dynamic> mat_;
    Eigen::Vector2i sz_;
    Eigen::Vector2d origin_;
    double r_;
};
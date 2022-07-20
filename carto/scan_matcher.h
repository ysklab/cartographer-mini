#pragma once

#include <Eigen/Dense>
#include <Eigen/Geometry>

using Mat2Xd = Eigen::Matrix2Xd;
using MatXd = Eigen::MatrixXd;
using Vec2d = Eigen::Vector2d;

struct GridMap {
    Eigen::MatrixXd data;
    Eigen::Array2i size;
    Eigen::Vector2d origin;
    double r;
};
struct Option {
    double x_range, y_range, th_range;
};
struct SearchWindow : Eigen::Array3d {
    double th() const { return z(); }
};
struct IntOffset : Eigen::Array3i {
    using Eigen::Array3i::Array3i;
    double th() const { return z(); }
};

double Score(const Eigen::Matrix2Xd& points, const GridMap& m, const Eigen::Affine2d& pose) {
    Eigen::Matrix2Xd aligned_points = pose * points;
    double s = 0;
    for (const auto& p : points) {
        s += m.PointValueOr(p, 0);
    }    
    return s;
}

double Match(const Eigen::Matrix2Xd& points, const GridMap& m, const Eigen::Affine2d& pose, const Option& opt, Eigen::Affine2d* out) {
  double r= m.resolution();
  double dmax = points.colwise().norm().maxCoeff();
  double dth = std::acos(1 - r * r / 2 / dmax / dmax);
  int offset_x = std::ceil(opt.x_range/m.r), offset_y = std::ceil(opt.y_range/m.r), offset_th = std::ceil(opt.th_range/dth);
  double best = 0;
  Eigen::Affine2d best_ps;
  for (int x_offset = -offset_x; x_offset <= offset_x; ++x_offset) {
    for (int y_offset = -offset_y; y_offset <= offset_y; ++y_offset) {
        for (int th_offset = -offset_th; th_offset <= offset_th; ++th_offset) {
            Eigen::Affine2d ps = pose;
            ps.rotate(th_offset * dth);
            ps.pretranslate(Eigen::Vector2d(x_offset,y_offset) * r);
            double score = Score(points, m, ps);
            if (score > best) { best = score; best_ps = ps; }
        }
    }
  }
  // Eigen::VectorXd::LinSpaced(6, 1, 4);
  *out = best_ps;
  return best;
}

double Match22() {
  
}


double Match2(const Eigen::Matrix2Xd& points, const GridMap& m, const Eigen::Affine2d& pose, const SearchWindow& window, Eigen::Affine2d* out) {
  double dmax = points.colwise().norm().maxCoeff();
  double dth = std::acos(1 - m.r * m.r / 2 / dmax / dmax);
  Eigen::Array3i t = (window.array() / Eigen::Array3d(m.r, m.r, dth)).ceil().cast<int>();
  IntOffset offset = t;
  return 0;
}

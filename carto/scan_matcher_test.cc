#include <Eigen/Dense>
#include "scan_matcher.h"
#include "io.h"
#include <iostream>
#include <fstream>
int main() {
  GridMap m;
  m.r = 0.1;
  m.size = {20, 20};
  std::cout << "ss20" << std::endl;
  m.origin = {0, 0};
  std::cout << "ss203"<< std::endl;;
  m.data.resize(20, 20);
  std::cout << "ss20"<< std::endl;;
  Eigen::Matrix2Xd points(2, 21);
  points << -1.0, -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0,
             0.0, 0.1,  0.2 , 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 0.9, 0.8, 0.7, 0.6, 0.5, 0.4, 0.3, 0.2, 0.1, 0.0;
  std::cout << "ss15"<< std::endl;;
  for (int x = 5; x < 15; ++x) {
    m.data(x, 15) = 0.6;
  }
  for (int y = 5; y <15; ++y) {
    m.data(15, y) = 0.6;
  }
  std::cout << "ss20"<< std::endl;;
  Eigen::Affine2d init = Eigen::Affine2d::Identity();
  
  init.pretranslate(Eigen::Vector2d{1.0, 1.0});


  Option opt{.x_range=5, .y_range=5, .th_range=M_PI/2};
  Eigen::Affine2d out;
  std::cout << "ss26"<< std::endl;;
   double s = Match(points, m, init, opt, &out);

  std::cout << init.matrix() <<std::endl;
  Eigen::Matrix2Xd aligned = out * points;
  std::cout <<points << std::endl;
  std::cout << out.matrix() << std::endl;
  std::cout <<aligned << std::endl;
  std::ofstream ofs("/home/senior/lab/carto/build/data.json");
  assert(ofs);
// #ofs << ToJson(init*points) << std::endl;
  // ofs << ToJson(m)<<std::endl;
  //ofs << ToJson(out * points) << std::endl; 
}
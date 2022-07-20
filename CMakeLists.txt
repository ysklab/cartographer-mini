cmake_minimum_required(VERSION 3.16)
project(carto)
include_directories(
    /usr/include/eigen3
)
#add_library(carto
  #carto/scan_matcher.cc
#)
add_executable(main
  carto/scan_matcher_test.cc
)
# target_link_libraries(main carto)
// ExtraDataset.h
//
// David Adams
// April 2020
//
// Struct describing an extra dataset to include in calibration plots.

#ifndef ExtraDataset_H
#define ExtraDataset_H

#include <string>

struct ExtraDataset {
  std::string name;
  int marker;
  int color;
  ExtraDataset(string a_name, int a_marker, int a_color)
  : name(a_name), marker(a_marker), color(a_color) { }
};

#endif

